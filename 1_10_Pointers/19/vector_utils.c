#include "vector_utils.h"

void display_vector(const int *tab, int size)
{
    if(size <= 0 || tab == NULL)
        return;
    for(int i = 0; i < size; i++)
        printf("%d ", *(tab + i));
    printf("\n");
}

int read_vector(int *tab, int size, int stop_value)
{
    if(size <= 0 || tab == NULL)
        return -1;
    int i = 0;
    while(size)
    {
        if(!scanf("%d", tab))
            return -2;
        if(*tab == stop_value)
            break;
        tab++;
        i++;
        size--;
    }
    return i;
}