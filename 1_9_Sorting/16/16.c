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

int separate_even_and_odd(int tab[], int size)
{
    int position = 0;
    for(int i = 0; i < size; i++)
        if(tab[i] % 2)
            swap(position++, i, tab);
    return position;
}

int sort_odd_asc_even_desc(int tab[], int size)
{
    int pivot = separate_even_and_odd(tab, size);
    if(pivot == 0)
        return quicksort_desc(0, size - 1, tab, size);
    if(pivot == size)
        return quicksort_asc(0, size - 1, tab, size);
    int asc = quicksort_asc(0, pivot - 1, tab, size);
    int desc = quicksort_desc(pivot, size - 1, tab, size);
    return asc && desc;
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
    sort_odd_asc_even_desc(tab, size);
    display_vector(tab, size);
    return 0;
}