#include "sort.h"

int selection_sort_asc(int tab[], int size)
{
    if(size <= 0)
        return 1;
    if(size == 1)
        return 0;
    for(int i = 0; i < size - 1; i++)
    {
        int min = i;
        for(int j = i + 1; j < size; j++)
        {
            if(tab[min] > tab[j])
                min = j;
        }
        int tmp = tab[min];
        tab[min] = tab[i];
        tab[i] = tmp;
        display_vector(tab, size);
    }
    return 0;
}

int selection_sort_desc(int tab[], int size)
{
    if(size <= 0)
        return 1;
    if(size == 1)
        return 0;
    for(int i = 0; i < size - 1; i++)
    {
        int max = i;
        for(int j = i + 1; j < size; j++)
        {
            if(tab[max] < tab[j])
                max = j;
        }
        int tmp = tab[max];
        tab[max] = tab[i];
        tab[i] = tmp;
        display_vector(tab, size);
    }
    return 0;
}

int selection_sort(int tab[], int size, enum direction dir)
{
    if(dir == ASCENDING)
        return selection_sort_asc(tab, size);
    if(dir == DESCENDING)
        return selection_sort_desc(tab, size);
    return 1;
}