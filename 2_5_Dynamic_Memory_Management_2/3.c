#include <stdio.h>
#include <stdlib.h>

int create_array_2d_2(int ***ptr, int width, int height)
{
    if(width <= 0 || height <= 0 || ptr == NULL)
        return 1;
    *ptr = malloc(sizeof(int*) * height);
    if(*ptr == NULL)
        return 2;
    for(int i = 0; i < height; i++)
    {
        *((*ptr) + i) = malloc(sizeof(int) * width);
        if(*((*ptr) + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*((*ptr) + i));
            free(*ptr);
            return 2;
        }
    }
    return 0;
}

void display_array_2d(int **ptr, int width, int height)
{
    if(ptr == NULL || width <= 0 || height <= 0)
        return;
    for(int i = 0; i < height; i++)
    {
        int *row = *(ptr + i);
        for(int j = 0; j < width; j++)
            printf("%d ", *(row + j));
        printf("\n");
    }
}

void destroy_array_2d(int ***ptr, int height)
{
    if(ptr == NULL || height <= 0)
        return;
    for(int i = 0; i < height; i++)
        if(*((*ptr) + i) != NULL)
            free(*((*ptr) + i));
    free(*ptr);
    *ptr = NULL;
}

int sum_row(int *ptr, int width)
{
    if(ptr == NULL || width <= 0)
        return -1;
    int sum = 0;
    for(int i = 0; i < width; i++)
        sum += *(ptr + i);
    return sum;
}

int sum_array_2d(int **ptr, int width, int height)
{
    if(ptr == NULL || width <= 0 || height <= 0)
        return -1;
    int sum = 0;
    for(int i = 0; i < height; i++)
        if(*(ptr + i) != NULL)
            sum += sum_row(*(ptr + i), width);
        else
            return -1;
    return sum;
}

int main(void)
{
    printf("Podaj szerokosc i wysokosc: ");
    int width = 0;
    int height = 0;
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(width <= 0 || height <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    int **array;
    
    if(create_array_2d_2(&array, width, height) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < height; i++)
    {
        int *row = *(array + i);
        for(int j = 0; j < width; j++)
        {
            if(scanf("%d", row + j) != 1)
            {
                printf("Incorrect input");
                destroy_array_2d(&array, height);
                return 1;
            }
        }
    }
    display_array_2d(array, width, height);
    for(int i = 0; i < height; i++)
        printf("%d\n", sum_row(*(array + i), width));
    printf("%d\n", sum_array_2d(array, width, height));
    destroy_array_2d(&array, height);
    return 0;
}