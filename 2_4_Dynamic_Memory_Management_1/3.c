#include <stdio.h>
#include <stdlib.h>

float* create_array(int N)
{
    if(N <= 0)
        return NULL;
    return malloc(sizeof(float) * N);
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
    float *array = create_array(n);
    if(array == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; i++)
        if(scanf("%f", array + i) != 1)
        {
            printf("Incorrect input");
            free(array);
            return 1;
        }
    for(int i = n - 1; i >= 0; i--)
        printf("%f ", *(array + i));
    free(array);
    return 0;
}