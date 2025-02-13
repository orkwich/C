#include "comparators.h"

int my_abs(int x)
{
    return (-x * (x < 0)) + (x * (x >= 0));
}

int num_len(int x)
{
    if(x == 0)
        return 1;
    int i = 0;
    while(x != 0)
    {
        x /= 10;
        i++;
    }
    return i;
}

int sum_digits(int x)
{
    if(x == 0)
        return 0;
    x = my_abs(x);
    int sum = 0;
    while(x != 0)
    {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int comp_int(int a, int b)
{
    return -(a < b) + (a > b);
}

int comp_int_abs(int a, int b)
{
    return -(my_abs(a) < my_abs(b)) + (my_abs(a) > my_abs(b));
}

int comp_int_length(int a, int b)
{
    return -(num_len(a) < num_len(b)) + (num_len(a) > num_len(b));
}

int comp_int_digits_sum(int a, int b)
{
    int sum_a = sum_digits(a);
    int sum_b = sum_digits(b);
    return -(sum_a < sum_b) + (sum_a > sum_b);
}

void swap(int i, int j, int tab[])
{
    if(i != j)
    {
        int tmp = *(tab + i);
        *(tab + i) = *(tab + j);
        *(tab + j) = tmp;
    }
}

int bubble_sort(int tab[], int size, int (*cmp)(int, int))
{
    if(size <= 0)
        return 1;
    for(int i = size - 1; i >= 0; i--)
    {
        int is_sorted = 1;
        for(int j = 1; j <= i; j++)
        {
            if(cmp(*(tab + j -1), *(tab + j)) == 1)
            {
                is_sorted = 0;
                swap(j - 1, j, tab);
            }
        }
        if(is_sorted)
            return 0;
    }
    return 0;
}

int sort_int(int tab[], int size, int (*cmp)(int, int))
{
    if(cmp == NULL || tab == NULL)
        return 1;
    return bubble_sort(tab, size, cmp);
}