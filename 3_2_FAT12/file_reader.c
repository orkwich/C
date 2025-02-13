#include "file_reader.h"
#include <string.h>
#include <ctype.h>

#define SECTOR_SIZE 512
#define ENTRY_LEN 32

struct disk_t* disk_open_from_file(const char* volume_file_name)
{
    if(volume_file_name == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    struct disk_t *disk = malloc(sizeof(struct disk_t));
    if(disk == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    disk->f = fopen(volume_file_name, "rb");
    if(disk->f == NULL)
    {
        errno = ENOENT;
        free(disk);
        return NULL;
    }
    fseek(disk->f, 0, SEEK_END);
    disk->size = ftell(disk->f);
    return disk;
}

int disk_read(struct disk_t *pdisk, int32_t first_sector, void *buffer, int32_t sectors_to_read)
{
    if(pdisk == NULL || buffer == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    if(first_sector + sectors_to_read > (int32_t)pdisk->size)
    {
        errno = ERANGE;
        return -1;
    }
    fseek(pdisk->f, first_sector * SECTOR_SIZE, SEEK_SET);
    return fread(buffer, SECTOR_SIZE, sectors_to_read, pdisk->f);
}

int disk_close(struct disk_t* pdisk)
{
    if(pdisk == NULL || pdisk->f == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    fclose(pdisk->f);
    free(pdisk);
    return 0;
}

int is_power_of_two(uint16_t n)
{
    for(uint16_t i = 0, j = 1; i < 16 && j <= n; i++, j <<= 1)
        if(j == n)
            return 1;
    return 0;
}

int is_boot_valid(struct bootSector_t *boot)
{
    if(boot->start.bytes_per_sector != SECTOR_SIZE)
        return 0;
    if(!is_power_of_two(boot->start.bytes_per_sector))
        return 0;
    if(boot->start.FATs == 0 || boot->start.max_files == 0)
        return 0;
    if((boot->start.sectors1 != 0 && boot->start.sectors2 != 0) || (boot->start.sectors1 == 0 && boot->start.sectors2 == 0))
        return 0;
    if(boot->signature_val != 0xaa55)
        return 0;
    return 1;
}

struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector)
{
    if(pdisk == NULL || pdisk->f == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    struct volume_t *vol = malloc(sizeof(struct volume_t));
    if(vol == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    vol->pdisk = pdisk;
    uint32_t cur_sec = first_sector;
    if(disk_read(pdisk, cur_sec, vol, 1) == -1)
    {
        free(vol);
        return NULL;
    }
    if(!is_boot_valid(&vol->boot))
    {
        errno = EINVAL;
        free(vol);
        return NULL;
    }
    cur_sec += vol->boot.start.reserved;
    uint32_t bytes_per_FAT = vol->boot.start.sectors_per_FAT * vol->boot.start.bytes_per_sector;
    vol->fat_size = (size_t)bytes_per_FAT;
    vol->fat_buffer = malloc(sizeof(uint8_t) * bytes_per_FAT * vol->boot.start.FATs);
    if(vol->fat_buffer == NULL)
    {
        errno = ENOMEM;
        free(vol);
        return NULL;
    }
    if(disk_read(pdisk, cur_sec, vol->fat_buffer, vol->boot.start.sectors_per_FAT * vol->boot.start.FATs) == -1)
    {
        free(vol->fat_buffer);
        free(vol);
        return NULL;
    }
    for(uint8_t i = 1; i < vol->boot.start.FATs; i++)
        for(uint32_t j = 0; j < bytes_per_FAT; j++)
            if(*(vol->fat_buffer + j) != *(vol->fat_buffer + j + (bytes_per_FAT * i)))
            {
                errno = EINVAL;
                free(vol->fat_buffer);
                free(vol);
                return NULL;
            }
    vol->root_dir_size = vol->boot.start.max_files * ENTRY_LEN;
    vol->root_dir = malloc(sizeof(uint8_t) * vol->root_dir_size);
    if(vol->root_dir == NULL)
    {
        errno = ENOMEM;
        free(vol->fat_buffer);
        free(vol);
    }
    cur_sec += vol->boot.start.FATs * vol->boot.start.sectors_per_FAT;
    if(disk_read(pdisk, cur_sec, vol->root_dir, vol->root_dir_size / SECTOR_SIZE) == -1)
    {
        free(vol->fat_buffer);
        free(vol->root_dir);
        free(vol);
    }
    return vol;
}

int fat_close(struct volume_t *pvolume)
{
    if(pvolume == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    free(pvolume->fat_buffer);
    free(pvolume->root_dir);
    free(pvolume);
    return 0;
}

struct clusters_chain_t *get_chain_fat12(const void *const buffer, size_t size, uint16_t first_cluster)
{
    if(buffer == NULL || size == 0 || first_cluster == 0 || first_cluster == 1)
        return NULL;
    uint8_t *buff = (uint8_t *)buffer;
    uint16_t cur = first_cluster;
    size_t chain_size = 0;
    while(cur < 0xff8)
    {
        chain_size++;
        uint16_t byte = ((float)cur * 1.5) + 1;
        if(cur % 2 == 0)
        {
            uint16_t tmp = *(buff + byte);
            tmp <<= 12;
            tmp >>= 4;
            cur = tmp;
            cur += *(buff + byte - 1);
        } else
        {
            cur = *(buff + byte);
            cur <<= 4;
            cur += (*(buff + byte - 1)) >> 4;
        }
    }
    struct clusters_chain_t *chain = malloc(sizeof(struct clusters_chain_t));
    if(chain == NULL)
        return NULL;
    chain->size = chain_size;
    chain->clusters = malloc(sizeof(uint16_t) * chain_size);
    if(chain->clusters == NULL)
    {
        free(chain);
        return NULL;
    }
    cur = first_cluster;
    for(size_t i = 0; i < chain_size; i++)
    {
        *(chain->clusters + i) = cur;
        uint16_t byte = ((float)cur * 1.5) + 1;
        if(cur % 2 == 0)
        {
            uint16_t tmp = *(buff + byte);
            tmp <<= 12;
            tmp >>= 4;
            cur = tmp;
            cur += *(buff + byte - 1);
        } else
        {
            cur = *(buff + byte);
            cur <<= 4;
            cur += (*(buff + byte - 1)) >> 4;
        }
    }
    return chain;
}


int fname_cmp(const char* str1, const char* str2)
{
    if(*str2 == '.' || *str2 == '\0')
        return 1;
    int i;
    for(i = 0; i < 8; i++)
    {
        if(*(str2 + i) == '.' || *(str2 + i) == '\0')
            break;
        if(*(str1 + i) != *(str2 + i))
            return 1;
    }
    if(*(str2 + i) == '\0' && !isalpha(*(str1 + 8)))
        return 0;
    i++;
    int j = 8;
    while(j < 11 && *(str2 + i) != '\0')
        if(*(str1 + j++) != *(str2 + i++))
            return 1;
    return 0;
}

struct file_t* file_open(struct volume_t* pvolume, const char* file_name)
{
    if(pvolume == NULL || pvolume->pdisk == NULL || pvolume->fat_buffer == NULL || pvolume->root_dir == NULL || file_name == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    struct file_t *f = malloc(sizeof(struct file_t));
    if(f == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    f->vol = pvolume;
    f->cluster_buffor = malloc(sizeof(uint8_t) * SECTOR_SIZE * f->vol->boot.start.sectors_per_cluster);
    if(f->cluster_buffor == NULL)
    {
        errno = ENOMEM;
        free(f->chain);
        free(f);
        return NULL;
    }
    f->cursor = 0;
    f->vol = pvolume;
    size_t root_dir_count = f->vol->root_dir_size / ENTRY_LEN;
    f->first_cluster = 0;
    uint8_t *entry = f->vol->root_dir;
    for(size_t i = 0; i < root_dir_count; i++, entry += ENTRY_LEN)
    {
        if(*entry == 0x00 || *entry == 0xe5)
            continue;
        if(fname_cmp((const char *)entry, file_name) == 0)
            break;
        if(i == root_dir_count - 1)
            entry = NULL;
    }
    if(entry == NULL)
    {
        errno = ENOENT;
        free(f->cluster_buffor);
        free(f);
        return NULL;
    }
    if(*(entry + 11) & 0x10 || *(entry + 11) & 0x08)
    {
        errno = EISDIR;
        free(f->cluster_buffor);
        free(f);
        return NULL;
    }
    f->root_dir_entry = entry;
    f->first_cluster = *(entry + 27);
    f->first_cluster <<= 12;
    f->first_cluster >>= 4;
    f->first_cluster += *(entry + 26);
    f->chain = get_chain_fat12(f->vol->fat_buffer, f->vol->fat_size, f->first_cluster);
    if(f->chain == NULL)
    {
        errno = ENOMEM;
        free(f->cluster_buffor);
        free(f);
        return NULL;
    }
    f->size = *(uint32_t *)(entry + 28);
    return f;
}

int file_close(struct file_t* stream)
{
    if(stream == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    free(stream->chain->clusters);
    free(stream->chain);
    free(stream->cluster_buffor);
    free(stream);
    return 0;
}

uint32_t get_cluster_sector(uint16_t cluster, struct volume_t *vol)
{
    uint32_t sectors_before_data = 0;
    sectors_before_data += vol->boot.start.reserved;
    sectors_before_data += vol->boot.start.FATs * vol->boot.start.sectors_per_FAT;
    sectors_before_data += (vol->boot.start.max_files * ENTRY_LEN) / SECTOR_SIZE;
    return sectors_before_data + ((cluster - 2) * vol->boot.start.sectors_per_cluster);
}

size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream)
{
    if(ptr == NULL || size == 0 || nmemb == 0 || stream == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    uint8_t *buf = (uint8_t *)ptr;
    uint32_t bytes = 0;
    uint32_t cluster_i = stream->cursor / (SECTOR_SIZE * stream->vol->boot.start.sectors_per_cluster);
    while(bytes < size * nmemb)
    {
        if(stream->cursor == stream->size)
            break;
        if(disk_read(stream->vol->pdisk, get_cluster_sector(*(stream->chain->clusters + cluster_i++), stream->vol), stream->cluster_buffor, stream->vol->boot.start.sectors_per_cluster) == -1)
        {
            errno = ERANGE;
            return -1;
        }
        for(int i = stream->cursor % (SECTOR_SIZE * stream->vol->boot.start.sectors_per_cluster); i < (SECTOR_SIZE * stream->vol->boot.start.sectors_per_cluster) && bytes < size * nmemb; i++)
        {
            *(buf + bytes++) = *(stream->cluster_buffor + i);
            if(++stream->cursor == stream->size)
                break;
        }
    }
    return bytes / size;
}

int32_t file_seek(struct file_t* stream, int32_t offset, int whence)
{
    if(stream == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    if(whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET)
    {
        errno = EINVAL;
        return -1;
    }
    if(whence == SEEK_END && (offset > 0 || -offset >= (int32_t)stream->size))
    {
        errno = ENXIO;
        return -1;
    }
    if(whence == SEEK_SET && (offset < 0 || offset >= (int32_t)stream->size))
    {
        errno = ENXIO;
        return -1;
    }
    if(whence == SEEK_CUR && ((int32_t)stream->cursor + offset < 0 || (int32_t)stream->cursor + offset >= (int32_t)stream->size))
    {
        errno = ENXIO;
        return -1;
    }
    if(whence == SEEK_SET)
        stream->cursor = 0;
    if(whence == SEEK_END)
        stream->cursor = stream->size;
    stream->cursor += offset;
    return 0;
}

struct dir_t* dir_open(struct volume_t* pvolume, const char* dir_path)
{
    if(pvolume == NULL || pvolume->root_dir == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    if(dir_path == NULL || *dir_path != '\\')
    {
        errno = ENOENT;
        return NULL;
    }
    struct dir_t *dir = malloc(sizeof(struct dir_t));
    if(dir == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    dir->dir = pvolume->root_dir;
    dir->size = pvolume->root_dir_size;
    dir->last = 0;
    return dir;
}

int is_entry_valid(uint8_t *entry)
{
    if(*entry == 0x00 || *entry == 0xe5)
        return 0;
    if(*(uint16_t *)(entry + 20) != 0)
        return 0;
    uint8_t first_cluster = *(entry + 27);
    first_cluster <<= 12;
    first_cluster >>= 4;
    first_cluster += *(entry + 26);
    if(first_cluster < 2)
        return 0;
    if(*(entry + 11) == 0x10 && *(uint32_t *)(entry + 28) != 0)
        return 0;
    return 1;
}

void write_name(uint8_t *bytes, struct dir_entry_t *entry)
{
    int i;
    for(i = 0; i < 8; i++)
        if(isalpha((int)*(bytes + i)))
            *(entry->name + i) = (char)*(bytes + i);
        else
            break;
    if(*(bytes + 11) & 0x10 || !isalpha(*(bytes + 8)))
    {
        *(entry->name + i) = '\0';
        return;
    }
    *(entry->name + i++) = '.';
    for(int j = 8; j < 11; i++, j++)
        if(isalpha((int)*(bytes + j)))
            *(entry->name + i) = (char)*(bytes + j);
        else
            break;
    *(entry->name + i) = '\0';
}

void write_attribute(uint8_t *bytes, struct dir_entry_t *entry)
{
    entry->is_archived = 0;
    entry->is_directory = 0;
    entry->is_hidden = 0;
    entry->is_readonly = 0;
    entry->is_system = 0;
    if(*(bytes + 11) & 0x01)
    {
        entry->is_readonly = 1;
        return;
    }
    if(*(bytes + 11) & 0x02)
    {
        entry->is_hidden = 1;
        return;
    }
    if(*(bytes + 11) & 0x04)
    {
        entry->is_system = 1;
        return;
    }
    if(*(bytes + 11) & 0x10)
    {
        entry->is_directory = 1;
        return;
    }
    if(*(bytes + 11) & 0x20)
    {
        entry->is_archived = 1;
        return;
    }    
}

int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry)
{
    if(pdir == NULL || pentry == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    if(pdir->last >= pdir->size)
        return 1;
    for(size_t i = pdir->last; i < pdir->size; i += ENTRY_LEN)
    {
        if(!is_entry_valid(pdir->dir + i))
        {
            if(i + ENTRY_LEN >= pdir->size)
            {
                pdir->last = i + ENTRY_LEN;
                return 1;
            }
            continue;
        }
        write_name(pdir->dir + i, pentry);
        write_attribute(pdir->dir + i, pentry);
        pentry->size = *(uint32_t *)(pdir->dir + 28);
        pdir->last = i + ENTRY_LEN;
        break;
    }
    return 0;
}

int dir_close(struct dir_t* pdir)
{
    if(pdir == NULL)
    {
        errno = EFAULT;
        return -1;
    }
    free(pdir);
    return 0;
}