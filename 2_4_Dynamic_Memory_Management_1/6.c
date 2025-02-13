#include "array.h"

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
    struct array_t array;
    if(array_create(&array, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby do zapisania:\n");
    while(array.size < n)
    {
        int tmp = 0;
        if(scanf("%d", &tmp) != 1)
        {
            printf("Incorrect input");
            array_destroy(&array);
            return 1;
        }
        if(tmp == 0)
            break;
        array_push_back(&array, tmp);
        if(array.size == n)
            printf("Buffer is full\n");
    }
    if(array.size == 0)
        printf("Buffer is empty");
    else
        array_display(&array);
    array_destroy(&array);
    return 0;
}