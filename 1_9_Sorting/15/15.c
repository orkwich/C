#include "vector_utils.h"

void swap(int i, int j, int tab[])
{
    if(i != j)
    {
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
}

int divide_even_asc(int l, int r, int tab[])
{
    int pivot = (l + r) / 2;
    if(pivot % 2 != l % 2)
        pivot--;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i += 2)
        if(tab[r] > tab[i])
        {
            swap(position, i, tab);
            position += 2;
        }
    swap(position, r, tab);
    return position;
}

int divide_odd_desc(int l, int r, int tab[])
{
    int pivot = (l + r) / 2;
    if(pivot % 2 != l % 2)
        pivot--;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i += 2)
        if(tab[r] < tab[i])
        {
            swap(position, i, tab);
            position += 2;
        }
    swap(position, r, tab);
    return position;
}

int quicksort_even_asc(int l, int r, int tab[], int tabSize)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_even_asc(l, r, tab);
        quicksort_even_asc(l, pivot, tab, tabSize);
        quicksort_even_asc(pivot + 2, r, tab, tabSize);
    }
    return 0;
}

int quicksort_odd_desc(int l, int r, int tab[], int tabSize)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_odd_desc(l, r, tab);
        quicksort_odd_desc(l, pivot, tab, tabSize);
        quicksort_odd_desc(pivot + 2, r, tab, tabSize);
    }
    return 0;
}

int sort_odd_desc(int tab[], int size)
{
    if(size == 1)
        return 0;
    return quicksort_odd_desc(1, size - 1 - (size % 2), tab, size);
}
int sort_even_asc(int tab[], int size)
{
    return quicksort_even_asc(0, size - 1 - !(size % 2), tab, size);
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
    sort_even_asc(tab, size);
    sort_odd_desc(tab, size);
    display_vector(tab, size);
    return 0;
}