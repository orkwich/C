#include "vector_utils.h"

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int abs(int x)
{
    if(x < 0)
        return -x;
    return x;
}

int distance(int x, int y)
{
    return abs(x - y);
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

int divide_asc(int l, int r, int tab[], int v)
{
    int pivot = (l + r) / 2;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i++)
        if(distance(v, tab[r]) > distance(v, tab[i]))
            swap(position++, i, tab);
    swap(position, r, tab);
    return position;
}

int quicksort_asc(int l, int r, int tab[], int tabSize, int v)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_asc(l, r, tab, v);
        quicksort_asc(l, pivot, tab, tabSize, v);
        quicksort_asc(pivot + 1, r, tab, tabSize, v);
    }
    return 0;
}

int sort_by_distance(int tab[], int size, int v)
{
    return quicksort_asc(0, size - 1, tab, size, v);
}

int main(void)
{
    printf("Podaj wektor: ");
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
    clear();
    printf("Podaj wartosc: ");
    int v = 0;
    if(scanf("%d", &v) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    sort_by_distance(tab, size, v);
    display_vector(tab, size);
    return 0;
}