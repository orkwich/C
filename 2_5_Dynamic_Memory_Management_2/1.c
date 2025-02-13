#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main(void)
{
    int **tab = malloc(sizeof(int*) * SIZE);
    if(tab == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < SIZE; i++)
    {
        *(tab + i) = malloc(sizeof(int) * SIZE);
        if(*(tab + i) == NULL)
        {
            printf("Failed to allocate memory");
            for(int j = i; j >= 0; j--)
                free(*(tab + j));
            free(tab);
            return 8;
        }
    }
    for(int i = 0; i < SIZE; i++)
    {
        int *row = *(tab + i);
        for(int j = 0; j < SIZE; j++)
            *(row + j) = (j + 1) * (i + 1);
    }
    for(int i = 0; i < SIZE; i++)
    {
        int *row = *(tab + i);
        for(int j = 0; j < SIZE; j++)
            printf("%3d ", *(row + j));
        printf("\n");
    }
    for(int i = 0; i < SIZE; i++)
        free(*(tab + i));
    free(tab);
    return 0;
}