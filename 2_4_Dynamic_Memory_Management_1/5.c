#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* create_array_int(int N)
{
    if(N <= 0)
        return NULL;
    return malloc(sizeof(int) * N);
}

int* copy_array_int(const int* ptr, int N)
{
    if(ptr == NULL || N <= 0)
        return NULL;
    int *cpy = malloc(sizeof(int) * N);
    if(cpy == NULL)
        return NULL;
    return memcpy(cpy, ptr, sizeof(int) * N);
}

void display_array_int(const int* ptr, int N)
{
    if(ptr == NULL || N <= 0)
        return;
    for(int i = 0; i < N; i++)
        printf("%d ", *(ptr + i));
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
    int *array = create_array_int(n);
    if(array == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++)
        if(scanf("%d", array + i) != 1)
        {
            printf("Incorrect input");
            free(array);
            return 1;
        }
    int *cpy = copy_array_int(array, n);
    if(cpy == NULL)
    {
        printf("Failed to allocate memory");
        free(array);
        return 8;
    }
    display_array_int(array, n);
    printf("\n");
    display_array_int(cpy, n);
    free(array);
    free(cpy);
    return 0;
}