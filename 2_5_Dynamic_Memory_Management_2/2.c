#include <stdio.h>
#include <stdlib.h>

int **create_array_2d(int width, int height)
{
    if(width <= 0 || height <= 0)
        return NULL;
    int **array = malloc(sizeof(int*) * height);
    if(array == NULL)
        return NULL;
    for(int i = 0; i < height; i++)
    {
        *(array + i) = malloc(sizeof(int) * width);
        if(*(array + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*(array + i));
            free(array);
            return NULL;
        }
    }
    return array;
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

void destroy_array_2d(int **ptr, int height)
{
    if(ptr == NULL || height <= 0)
        return;
    for(int i = 0; i < height; i++)
        if(*(ptr + i) != NULL)
            free(*(ptr + i));
    free(ptr);
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
    int **array = create_array_2d(width, height);
    if(array == NULL)
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
                destroy_array_2d(array, height);
                return 1;
            }
        }
    }
    display_array_2d(array, width, height);
    destroy_array_2d(array, height);
    return 0;
}