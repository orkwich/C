#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "format_type.h"
#define FNAME_SIZE 40

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int load_txt(const char *filename, int ***ptr)
{
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 2;
    int height = 0;
    int tmp = 0;
    int ret = 0;
    while((ret = fscanf(f, "%d", &tmp)) != EOF)
    {
        if(tmp == -1)
            height++;
        if(ret == 0)
        {
            fclose(f);
            return 3;
        }
    }
    if(height == 0)
    {
        fclose(f);
        return 3;
    }
    height++;
    int **tmp_ptr = malloc(sizeof(int*) * height);
    if(tmp_ptr == NULL)
    {
        fclose(f);
        return 4;
    }
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < height - 1; i++)
    {
        int width = 0;
        tmp = 0;
        while(tmp != -1)
        {
            if(fscanf(f, "%d", &tmp) != 1)
            {
                for(--i; i >= 0; i--)
                    free(*(tmp_ptr + i));
                free(tmp_ptr);
                fclose(f);
                return 3;
            }
            width++;
        }
        *(tmp_ptr + i) = malloc(sizeof(int) * width);
        if(*(tmp_ptr + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*(tmp_ptr + i));
            free(tmp_ptr);
            fclose(f);
            return 4;
        }
    }
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < height - 1; i++)
    {
        int width = 0;
        tmp = 0;
        while(tmp != -1)
        {
            if(fscanf(f, "%d", &tmp) != 1)
            {
                for(; i >= 0; i--)
                    free(*(tmp_ptr + i));
                free(tmp_ptr);
                fclose(f);
                return 3;
            }
            *(*(tmp_ptr + i) + width++) = tmp;
        }
    }
    *(tmp_ptr + height - 1) = NULL;
    *ptr = tmp_ptr;
    fclose(f);
    return 0;
}

int load_bin(const char *filename, int ***ptr)
{
    FILE *f = fopen(filename, "rb");
    if(f == NULL)
        return 2;
    int buf = 0;
    int height = 0;
    while(fread(&buf, sizeof(int), 1, f))
        if(buf == -1)
            height++;
    if(!feof(f) || buf != -1)
    {
        fclose(f);
        return 3;
    }
    height++;
    int **tmp_ptr = malloc(sizeof(int*) * height);
    if(tmp_ptr == NULL)
    {
        fclose(f);
        return 4;
    }
    int i = 0;
    int j = 0;
    fseek(f, 0, SEEK_SET);
    while(fread(&buf, sizeof(int), 1, f))
    {
        j++;
        if(buf == -1)
        {
            *(tmp_ptr + i) = malloc(sizeof(int) * j);
            if(*(tmp_ptr + i) == NULL)
            {
                for(; i >= 0; i--)
                    free(*(tmp_ptr + i));
                free(tmp_ptr);
                fclose(f);
                return 4;
            }
            i++;
            j = 0;
        }
    }
    i = 0;
    j = 0;
    fseek(f, 0, SEEK_SET);
    while(fread(&buf, sizeof(int), 1, f))
    {
        *(*(tmp_ptr + i) + j++) = buf;
        if(buf == -1)
        {
            i++;
            j = 0;
        }
    }
    *(tmp_ptr + height - 1) = NULL;
    *ptr = tmp_ptr;
    fclose(f);
    return 0;
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
    if(filename == NULL || ptr == NULL || (format != fmt_text && format != fmt_binary))
        return 1;
    if(format == fmt_text)
        return load_txt(filename, ptr);
    if(format == fmt_binary)
        return load_bin(filename, ptr);
    return 1;
}

int min(int *tab)
{
    if(*tab == -1)
        return -1;
    int min = *tab;
    while(*(++tab) != -1)
        if(min > *tab)
            min = *tab;
    return min;
}

int max(int *tab)
{
    if(*tab == -1)
        return -1;
    int max = *tab;
    while(*(++tab) != -1)
        if(max < *tab)
            max = *tab;
    return max;
}

float avg(int *tab)
{
    if(*tab == -1)
        return -1;
    int sum = *tab;
    int n = 1;
    while(*(++tab) != -1)
    {
        sum += *tab;
        n++;
    }
    return (float)sum / n;
}

float standard_deviation(int *tab)
{
    if(*tab == -1)
        return -1;
    float a = avg(tab);
    float sum = 0;
    int n = 0;
    while(*tab != -1)
    {
        sum += (float)pow(*tab++ - a, 2);
        n++;    
    }
    return sqrtf((float)sum / n);
}

void fill_stats_err(struct statistic_t *stats)
{
    stats->min = -1;
    stats->max = -1;
    stats->avg = -1;
    stats->standard_deviation = -1;
    stats->range = -1;
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
    if(ptr == NULL || stats == NULL)
        return -1;
    int height = 0;
    while(*(ptr + height) != NULL)
        height++;
    if(height == 0)
        return -1;
    *stats = malloc(sizeof(struct statistic_t) * height);
    if(*stats == NULL)
        return -2;
    for(int i = 0; i < height; i++)
    {
        int *row = *(ptr + i);
        (*stats + i)->min = min(row);
        (*stats + i)->max = max(row);
        (*stats + i)->avg = avg(row);
        (*stats + i)->standard_deviation = standard_deviation(row);
        (*stats + i)->range = abs((*stats + i)->min - (*stats + i)->max);
        if((*stats + i)->min == -1 || (*stats + i)->max == -1 || (*stats + i)->avg == -1 || (*stats + i)->standard_deviation == -1)
            fill_stats_err(*stats + i);
    }
    return height;
}

void destroy(int ***ptr)
{
    if(ptr == NULL)
        return;
    int i = 0;
    while(*((*ptr) + i) != NULL)
        free(*((*ptr) + i++));
    free(*ptr);
    *ptr = NULL;
}

void display(int **ptr)
{
    if(ptr == NULL)
        return;
    int i = 0;
    while(*(ptr + i) != NULL)
    {
        int j = 0;
        int *row = *(ptr + i++);
        while(*(row + j) != -1)
            printf("%d ", *(row + j++));
        printf("\n");
    }
}

int check_format(char *filename)
{
    int len = strlen(filename);
    if(strcmp(filename + len - 4, ".txt") == 0)
        return 1;
    if(strcmp(filename + len - 4, ".bin") == 0)
        return 2;
    return 0;
}

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    char *fname = malloc(sizeof(char) * FNAME_SIZE);
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pliku: ");
    scanf("%39s", fname);
    int format = check_format(fname);
    if(format == 0)
    {
        printf("Unsupported file format");
        free(fname);
        return 7;
    }
    int **arr;
    int res = load(fname, &arr, (enum save_format_t)format);
    free(fname);
    if(res == 2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(res == 3)
    {
        printf("File corrupted");
        return 6;
    }
    if(res == 4)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    struct statistic_t *stats;
    int size = statistics_row(arr, &stats);
    if(size == -2)
    {
        printf("Failed to allocate memory");
        destroy(&arr);
        return 8;
    }
    for(int i = 0; i < size; i++)
        printf("%d %d %d %.2f %.2f\n", (stats + i)->min, (stats + i)->max, (stats + i)->range, (stats + i)->avg, (stats + i)->standard_deviation);
    free(stats);
    destroy(&arr);
    return 0;
}