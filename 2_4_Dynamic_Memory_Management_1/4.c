#include <stdio.h>
#include <stdlib.h>

int create_array_int(int **ptr, int N)
{
    if(N <= 0 || ptr == NULL)
        return 1;
    *ptr = malloc(sizeof(int) * N);
    if(*ptr == NULL)
        return 2;
    return 0;
}

void destroy_array_int(int **ptr)
{
    if(ptr == NULL || *ptr == NULL)
        return;
    free(*ptr);
    *ptr = NULL;
}

int main(void)
{
    printf("Podaj rozmiar tablicy: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    int *array;
    if(create_array_int(&array, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++)
        if(scanf("%d", array + i) != 1)
        {
            printf("Incorrect input");
            destroy_array_int(&array);
            return 1;
        }
    for(int i = n - 1; i >= 0; i--)
        printf("%d ", *(array + i));
    destroy_array_int(&array);
    return 0;
}