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

void display_vector(const int vec[], int size)
{
    if(size <= 0)
        return;
    for(int i = 0; i < size; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

void shift(int array[], int firstIndex, int lastIndex)
{
    if(firstIndex == lastIndex) array[firstIndex] = !array[firstIndex];
    for(int i = firstIndex; i < lastIndex; i++)
        array[i] = array[i+1];
}

int deleteRepeats(int array[], int lastIndex)
{
    int i;
    int j;
    for(i = 0; i < lastIndex; i++)
        for(j = i + 1; j <= lastIndex; j++)
            while(array[i] == array[j] && i < lastIndex)
                shift(array, j, lastIndex--);

    return lastIndex;
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
    tab_size = deleteRepeats(tab, tab_size);
    display_vector(tab, tab_size);
    return 0;
}