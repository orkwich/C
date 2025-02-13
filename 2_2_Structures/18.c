#include <stdio.h>
#define FILE_NAME_LEN 999
#define FCOUNT 5

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename)
{
    if(f == NULL || filename == NULL)
        return 1;
    f->f = fopen(filename, "a+");
    if(f->f == NULL)
        return 2;
    fseek(f->f, 0, SEEK_END);
    f->size = ftell(f->f);
    return 0;
}

struct file_t* find_min(const struct file_t* files, int size)
{
    if(size <= 0 || files == NULL)
        return NULL;
    int min_size = files->size;
    int min_idx = 0;
    for(int i = 1; i < size; i++)
        if(min_size > (files + i)->size)
        {
            min_size = (files + i)->size;
            min_idx = i;
        }
    return (struct file_t*)files + min_idx;
}

void close_file(struct file_t* f)
{
    if(f == NULL || f->f == NULL)
        return;
    fclose(f->f);
}

void printf_to_file(struct file_t *f, char *str)
{
    if(f == NULL || f->f == NULL)
        return;
    fseek(f->f, -1, SEEK_END);
    fprintf(f->f, "%s\n", str);
    fseek(f->f, 0, SEEK_END);
    f->size = ftell(f->f);
}

int main(void)
{
    printf("Podaj nazwy plikow:\n");
    struct file_t tab[FCOUNT];
    int files_opend_count = 0;
    char str[FILE_NAME_LEN + 1];
    char c;
    while((c = getc(stdin)) != '\n')
    {
        ungetc(c, stdin);
        scanf("%999s", str);
        while((c = getchar()) != '\n' && c != '\0');
        if(files_opend_count < FCOUNT && open_file(tab + files_opend_count, str) == 0)
            files_opend_count++;
    }
    if(!files_opend_count)
    {
        printf("Couldn't open file");
        return 4;
    }
    printf("Podaj teksty:\n");
    while((c = getc(stdin)) != '\n')
    {
        ungetc(c, stdin);
        scanf("%999[^\n]", str);
        while((c = getchar()) != '\n' && c != '\0');
        struct file_t* tmp_min = find_min(tab, files_opend_count);
        printf_to_file(tmp_min, str);
    }
    for(int i = 0; i < files_opend_count; i++)
        close_file(tab + i);
    printf("Files saved");
    return 0;
}