#include "vector_utils.h"
#define SIZE 100
#define STOP -1

int find_min(const int* tab, int size, int *min)
{
    if(size <= 0 || tab == NULL || min == NULL)
        return 1;
    *min = *tab;
    for(int i = 1; i < size; i++)
        if(*(tab + i) < *min)
            *min = *(tab + i);
    return 0;
}

int main(void)
{
    printf("podaj liczby: ");
    int tab[SIZE];
    int size = SIZE;
    size = read_vector(tab, size, STOP);
    if(size == 0 || size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    int min = 0;
    find_min(tab, size, &min);
    printf("Min: %d", min);
    return 0;
}