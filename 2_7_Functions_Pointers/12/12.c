#include "functions.h"

int main(void)
{
    printf("Podaj liczbe funkcji do wygenerowania: ");
    int size = 0;
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    void (**funcs)(void) = easter(size, &print_chicken, &print_egg, &print_rabbit);
    if(funcs == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < size; i++)
    {
        (*(funcs + i))();
        printf("\n");
    }
    free(funcs);
    return 0;
}