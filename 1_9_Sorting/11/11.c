#include "vector_utils.h"

int abs(int x)
{
    if(x < 0)
        return -x;
    return x;
}

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
        if(abs(tab[r]) > abs(tab[i]))
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

int sort_by_abs(int tab[], int size)
{
    return quicksort_asc(0, size - 1, tab, size);
}

int main(void)
{
    printf("Podaj wektor:\n");
    int tab[MAX_SIZE];
    int size = MAX_SIZE;
    size = read_vector(tab, size, STOP);
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    sort_by_abs(tab, size);
    display_vector(tab, size);
    return 0;
}