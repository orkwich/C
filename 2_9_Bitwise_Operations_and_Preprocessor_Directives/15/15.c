#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#define FNAME_SIZE 30

DEFINE_ARRAY(int)
DEFINE_ARRAY(double)

CREATE_ARRAY(int)
CREATE_ARRAY(double)

FREE_ARRAY(int)
FREE_ARRAY(double)

SAVE_ARRAY(int)
SAVE_ARRAY(double)

LOAD_ARRAY(int)
LOAD_ARRAY(double)

SORT_ARRAY(int)
SORT_ARRAY(double)

int main(void)
{
    char *fname = malloc(sizeof(char) * (FNAME_SIZE + 1));
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter filename: ");
    scanf("%30s", fname);
    printf("Choose your type: ");
    int type;
    if(scanf("%d", &type) != 1)
    {
        printf("Incorrect input");
        free(fname);
        return 1;
    }
    if(type != 0 && type != 1)
    {
        printf("Incorrect input data");
        free(fname);
        return 2;
    }
    if(type == 0)
    {
        struct array_int_t *arr;
        int res = load_array_int(&arr, fname);
        if(res == 2)
        {
            printf("Couldn't open file");
            free(fname);
            return 4;
        }
        if(res == 3)
        {
            printf("File corrupted");
            free(fname);
            return 6;
        }
        if(res == 4)
        {
            printf("Failed to allocate memory");
            free(fname);
            return 8;
        }
        sort_array_int(arr);
        if(save_array_int((const struct array_int_t *)arr, fname) == 2)
        {
            printf("Couldn't create file");
            free(fname);
            free_array_int(arr);
            return 5;
        }
        free_array_int(arr);
    }
    if(type == 1)
    {
        struct array_double_t *arr;
        int res = load_array_double(&arr, fname);
        if(res == 2)
        {
            printf("Couldn't open file");
            free(fname);
            return 4;
        }
        if(res == 3)
        {
            printf("File corrupted");
            free(fname);
            return 6;
        }
        if(res == 4)
        {
            printf("Failed to allocate memory");
            free(fname);
            return 8;
        }
        sort_array_double(arr);
        if(save_array_double((const struct array_double_t *)arr, fname) == 2)
        {
            printf("Couldn't create file");
            free(fname);
            free_array_double(arr);
            return 5;
        }
        free_array_double(arr);
    }
    free(fname);
    printf("File saved");
    return 0;
}