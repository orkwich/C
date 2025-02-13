#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

CREATE_READ_FUNCTIONS(int, "%d")
CREATE_SORT_FUNCTIONS(int)
CREATE_DISPLAY_FUNCTIONS(int, "%d")

CREATE_READ_FUNCTIONS(float, "%f")
CREATE_SORT_FUNCTIONS(float)
CREATE_DISPLAY_FUNCTIONS(float, "%f")

CREATE_READ_FUNCTIONS(double, "%lf")
CREATE_SORT_FUNCTIONS(double)
CREATE_DISPLAY_FUNCTIONS(double, "%lf")

int main(void)
{
    printf("Choose your type: ");
    int type = 0;
    if(scanf("%d", &type) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(type < 0 || type > 2)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Podaj rozmiar tablicy: ");
    int size = 0;
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    if(type == 0)
    {
        int *arr = malloc(sizeof(int) * size);
        if(arr == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Podaj liczby:\n");
        if(read_int(arr, size) == 2)
        {
            printf("Incorrect input");
            free(arr);
            return 1;
        }
        sort_int(arr, size);
        display_int(arr, size);
        free(arr);
    }
    if(type == 1)
    {
        float *arr = malloc(sizeof(float) * size);
        if(arr == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Podaj liczby:\n");
        if(read_float(arr, size) == 2)
        {
            printf("Incorrect input");
            free(arr);
            return 1;
        }
        sort_float(arr, size);
        display_float(arr, size);
        free(arr);
    }
    if(type == 2)
    {
        double *arr = malloc(sizeof(double) * size);
        if(arr == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Podaj liczby:\n");
        if(read_double(arr, size) == 2)
        {
            printf("Incorrect input");
            free(arr);
            return 1;
        }
        sort_double(arr, size);
        display_double(arr, size);
        free(arr);
    }
    return 0;
}