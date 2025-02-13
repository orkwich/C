#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main(void)
{
    int *tab = malloc(sizeof(int) * SIZE);
    if(tab == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < SIZE; i++)
        *(tab + i) = i;
    for(int i = 0; i < SIZE; i++)
        printf("%d ", *(tab + i));
    free(tab);
    return 0;
}