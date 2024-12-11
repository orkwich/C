#include <stdio.h>
#define SIZE 100
#define STOP 0

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
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

int main(void)
{
    printf("podaj pierwszy ciag:\n");
    int tab1[SIZE];
    int tab1_size = SIZE;
    tab1_size = read_vector(tab1, tab1_size, STOP);
    if(tab1_size == -2)
    {
        printf("incorrect input");
        return 1;
    }
    clear();
    printf("podaj drugi ciag:\n");
    int tab2[SIZE];
    int tab2_size = SIZE;
    tab2_size = read_vector(tab2, tab2_size, STOP);
    if(tab2_size == -2)
    {
        printf("incorrect input");
        return 1;
    }
    if(tab2_size == -1 || tab1_size == -1)
    {
        printf("not enough data available");
        return 2;
    }
    for(int i = 0; i < tab1_size && i < tab2_size; i++)
        printf("%d ", tab1[i] - tab2[i]);
    return 0;
}