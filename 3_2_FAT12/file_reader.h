#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

struct disk_t
{
    FILE *f;
    size_t size;
};
struct disk_t* disk_open_from_file(const char* volume_file_name);
int disk_read(struct disk_t* pdisk, int32_t first_sector, void* buffer, int32_t sectors_to_read);
int disk_close(struct disk_t* pdisk);

struct __attribute__((packed)) bootSectorBegin_t
{
    uint8_t boot_code[3];
    int8_t OEM_name[8];
    uint16_t bytes_per_sector; //(512, 1024, 2048, or 4096)
    uint8_t sectors_per_cluster; //(Must be a power of 2 and cluster size must be <=32 KB)
    uint16_t reserved;
    uint8_t FATs; //(usually 2)
    uint16_t max_files; //(FAT12/16; 0 for FAT32)
    uint16_t sectors1; //if 2B is not large enough, set to 0 and use 4B (32-35 (sector2))
    uint8_t media_type; //(0xf0=removable disk, 0xf8=fixed disk)
    uint16_t sectors_per_FAT; //(for FAT12/16; 0 for FAT32)
    uint16_t sectors_per_track; //in storage device
    uint16_t heads; //in storage device
    uint32_t sectors_before_start;
    uint32_t sectors2; //this field will be 0 if the 2B field above (bytes 19-20) is non-zero
};

struct __attribute__((packed)) bootSector_t
{
    struct bootSectorBegin_t start;
    uint8_t BIOS_INT_13h;
    uint8_t not_used;
    uint8_t extended_boot_signature; //to validate next three fields (0x29)
    uint32_t volume_serial_number;
    uint8_t valume_label[11]; //ASCII
    uint8_t fs_type_level[8]; //ASCII
    uint8_t not_used2[448];
    uint16_t signature_val; //(0xaa55)
};

struct volume_t
{
    struct bootSector_t boot;
    struct disk_t *pdisk;
    uint8_t *fat_buffer;
    size_t fat_size;
    uint8_t *root_dir;
    size_t root_dir_size;
};
struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector);
int fat_close(struct volume_t* pvolume);

struct clusters_chain_t
{
    uint16_t *clusters;
    size_t size;
};

struct file_t
{
    struct volume_t *vol;
    uint8_t *root_dir_entry;
    uint16_t first_cluster;
    uint32_t cursor;
    struct clusters_chain_t *chain;
    uint8_t *cluster_buffor;
    uint32_t size;
};
struct file_t* file_open(struct volume_t* pvolume, const char* file_name);
int file_close(struct file_t* stream);
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream);
int32_t file_seek(struct file_t* stream, int32_t offset, int whence);

struct dir_entry_t
{
    char name[13];
    uint32_t size;
    uint8_t is_archived;
    uint8_t is_readonly;
    uint8_t is_system;
    uint8_t is_hidden;
    uint8_t is_directory;
};

struct dir_t
{
    uint8_t *dir;
    size_t size;
    size_t last;
};
struct dir_t* dir_open(struct volume_t* pvolume, const char* dir_path);
int dir_read(struct dir_t* pdir, struct dir_entry_t* pentry);
int dir_close(struct dir_t* pdir);

#endif