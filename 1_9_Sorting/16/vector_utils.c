#include "vector_utils.h"

void display_vector(const int vec[], int size)
{
    if(size <= 0)
        return;
    for(int i = 0; i < size; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

int read_vector(int vec[], int size, int stop_value)
{
    if(size <= 0)
        return -1;
    int i = 0;
    while(size)
    {
        if(!scanf("%d", vec))
            return -2;
        if(*vec == stop_value)
            break;
        vec++;
        i++;
        size--;
    }
    if(!i)
        return -1;
    return i;
}