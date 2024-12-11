#include "quicksort.h"

void swap(int i, int j, int tab[])
{
    if(i != j)
    {
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
}

int divide_asc(int l, int r, int tab[])
{
    int pivot = (l + r) / 2;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i++)
        if(tab[r] > tab[i])
            swap(position++, i, tab);
    swap(position, r, tab);
    return position;
}

int divide_desc(int l, int r, int tab[])
{
    int pivot = (l + r) / 2;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i++)
        if(tab[r] < tab[i])
            swap(position++, i, tab);
    swap(position, r, tab);
    return position;
}

int quicksort_asc(int l, int r, int tab[], int tabSize)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_asc(l, r, tab);
        quicksort_asc(l, pivot, tab, tabSize);
        quicksort_asc(pivot + 1, r, tab, tabSize);
    }
    return 0;
}

int quicksort_desc(int l, int r, int tab[], int tabSize)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_desc(l, r, tab);
        quicksort_desc(l, pivot, tab, tabSize);
        quicksort_desc(pivot + 1, r, tab, tabSize);
    }
    return 0;
}

int quicksort(int tab[], int size, enum direction dir)
{
    if(dir == ASCENDING)
        return quicksort_asc(0, size - 1, tab, size);
    if(dir == DESCENDING)
        return quicksort_desc(0, size - 1, tab, size);
    return 1;
}