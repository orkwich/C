#include "vector_utils.h"
#define SIZE 100
#define STOP 0

int swap(int *a, int *b)
{
    if(a == NULL || b == NULL)
        return 1;
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}

int reverse_vector(int* tab, int size)
{
    if(size <= 0 || tab == NULL)
        return 1;
    for(int i = 0, j = size - 1; i < j; i++, j--)
        swap(tab + i, tab + j);
    return 0;
}

int main(void)
{
    printf("Wprowadz liczby: ");
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
    display_vector(tab, size);
    reverse_vector(tab, size);
    display_vector(tab, size);
    return 0;
}