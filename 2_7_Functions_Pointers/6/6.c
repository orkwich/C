#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"
#define CMP_COUNT 4

int main(void)
{
    int (**funcs)() = malloc(sizeof(int (*)()) * CMP_COUNT);
    if(funcs == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    *funcs = &comp_int;
    *(funcs + 1) = &comp_int_abs;
    *(funcs + 2) = &comp_int_length;
    *(funcs + 3) = &comp_int_digits_sum;
    printf("Podaj dlugosc tablicy: ");
    int size = 0;
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if(size <= 0)
    {
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }
    int *tab = malloc(sizeof(int) * size);
    if(tab == NULL)
    {
        printf("Failed to allocate memory");
        free(funcs);
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < size; i++)
        if(scanf("%d", tab + i) != 1)
        {
            printf("Incorrect input");
            free(funcs);
            free(tab);
            return 1;
        }
    printf("Podaj rodzaj operacji: ");
    int op = -1;
    if(scanf("%d", &op) != 1)
    {
        printf("Incorrect input");
        free(funcs);
        free(tab);
        return 1;
    }
    if(op < 0 || op > 3)
    {
        printf("Incorrect input data");
        free(funcs);
        free(tab);
        return 2;
    }
    sort_int(tab, size, *(funcs + op));
    free(funcs);
    for(int i = 0; i < size; i++)
        printf("%d ", *(tab + i));
    free(tab);
    return 0;
}