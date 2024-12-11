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

int min(int vec[], int size)
{
    int min = vec[0];
    for(int i = 1; i < size; i++)
        if(min > vec[i])
            min = vec[i];
    return min;
}

int max(int vec[], int size)
{
    int max = vec[0];
    for(int i = 1; i < size; i++)
        if(max < vec[i])
            max = vec[i];
    return max;
}

int main(void)
{
    printf("podaj liczby: ");
    int tab[SIZE];
    int tab_size = SIZE;
    if((tab_size = read_vector(tab, tab_size, STOP)) == -1 || tab_size == 1)
    {
        printf("not enough data available");
        return 2;
    }
    if(tab_size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    int minimum = min(tab, tab_size);
    int maximum = max(tab, tab_size);
    int min_index = 0;
    int max_index = 0;
    for(int i = 0; i < tab_size; i++)
        if(minimum == tab[i])
        {
            min_index = i;
            break;
        }
    for(int i = 0; i < tab_size; i++)
        if(maximum == tab[i])
        {
            max_index = i;
            break;
        }
    int result_index = (min_index + max_index) / 2;
    printf("%d", tab[result_index]);
    return 0;
}