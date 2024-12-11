#include "vector_utils.h"
#define SIZE 150

int bubble_sort(int tab[], int size)
{
    if(size <= 0)
        return 1;
    for(int i = size - 1; i >= 0; i--)
    {
        int is_sorted = 1;
        for(int j = 1; j <= i; j++)
        {
            if(tab[j - 1] > tab[j])
            {
                is_sorted = 0;
                int tmp = tab[j - 1];
                tab[j - 1] = tab[j];
                tab[j] = tmp;
            }
        }
        display_vector(tab, size);
        if(is_sorted)
            return 0;
    }
    return 0;
}

int main(void)
{
    printf("Podaj wektor:\n");
    int vec[SIZE];
    int size = SIZE;
    size = read_vector(vec, size, 0);
    if(size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    bubble_sort(vec, size);
    return 0;
}