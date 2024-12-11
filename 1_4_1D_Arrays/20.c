#include <stdio.h>
#define SIZE 100
#define STOP 0

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

int main(void)
{
    printf("podaj liczby: ");
    int tab[SIZE];
    int tab_size = SIZE;
    if((tab_size = read_vector(tab, tab_size, STOP)) == -1)
    {
        printf("not enough data available");
        return 2;
    }
    if(tab_size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    int i = tab_size - 1;
    if(i % 2 == 1)
        i--;
    for(;i >= 0; i -= 2)
        printf("%d ", tab[i]);
    return 0;
}