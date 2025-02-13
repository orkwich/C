#include <stdlib.h>
#include "comparators.h"

void free_arr(int **tab, int size)
{
    for(int i = 0; i < size; i++)
        free(*(tab + i));
    free(tab);
}

int main(void)
{
    printf("Enter width and height: ");
    int cols = 0;
    int rows = 0;
    if(scanf("%d %d", &cols, &rows) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(cols <= 0 || rows <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    int **tab = malloc(sizeof(int*) * rows);
    if(tab == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < rows; i++)
    {
        *(tab + i) = malloc(sizeof(int) * cols);
        if(*(tab + i) == NULL)
        {
            printf("Failed to allocate memory");
            for(; i >= 0; i--)
                free(*(tab + i));
            free(tab);
            return 8;
        }
    }
    printf("Enter data:\n");
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(scanf("%d", *(tab + i) + j) != 1)
            {
                printf("Incorrect input");
                free_arr(tab, rows);
                return 1;
            }
    printf("Selection choice: ");
    int selection = -1;
    if(scanf("%d", &selection) != 1)
    {
        printf("Incorrect input");
        free_arr(tab, rows);
        return 1;
    }
    if(selection < 0 || selection > 2)
    {
        printf("Incorrect input data");
        free_arr(tab, rows);
        return 2;
    }
    int (**comps)(const int *, const int *, int) = malloc(sizeof(int(*)(const int *, const int *, int)) * 3);
    *comps = &comp_min;
    *(comps + 1) = &comp_max;
    *(comps + 2) = &comp_sum;
    sort_rows(tab, cols, rows, *(comps + selection));
    free(comps);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            printf("%d ", *(*(tab + i) + j));
        printf("\n");
    }
    free_arr(tab, rows);
    return 0;
}