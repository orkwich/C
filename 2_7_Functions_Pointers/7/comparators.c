#include "comparators.h"

int min(const int *ptr, int width)
{
    int min = *ptr;
    for(int i = 1; i < width; i++)
        if(min > *(ptr + i))
            min = *(ptr + i);
    return min;
}

int max(const int *ptr, int width)
{
    int max = *ptr;
    for(int i = 1; i < width; i++)
        if(max < *(ptr + i))
            max = *(ptr + i);
    return max;
}

int sum(const int *ptr, int width)
{
    int sum = 0;
    for(int i = 0; i < width; i++)
        sum += *(ptr + i);
    return sum;
}

int comp_min(const int *ptr1, const int *ptr2, int width)
{
    if(ptr1 == NULL || ptr2 == NULL || width <= 0)
        return 2;
    int min1 = min(ptr1, width);
    int min2 = min(ptr2, width);
    return -(min1 < min2) + (min1 > min2);
}

int comp_max(const int *ptr1, const int *ptr2, int width)
{
    if(ptr1 == NULL || ptr2 == NULL || width <= 0)
        return 2;
    int max1 = max(ptr1, width);
    int max2 = max(ptr2, width);
    return -(max1 < max2) + (max1 > max2);
}

int comp_sum(const int *ptr1, const int *ptr2, int width)
{
    if(ptr1 == NULL || ptr2 == NULL || width <= 0)
        return 2;
    int sum1 = sum(ptr1, width);
    int sum2 = sum(ptr2, width);
    return -(sum1 < sum2) + (sum1 > sum2);
}

void swap(int i, int j, int **tab)
{
    if(i != j)
    {
        int *tmp = *(tab + i);
        *(tab + i) = *(tab + j);
        *(tab + j) = tmp;
    }
}

int bubble_sort(int **tab, int cols, int rows, int (*cmp)(const int *, const int *, int))
{
    if(rows <= 0)
        return 1;
    for(int i = rows - 1; i >= 0; i--)
    {
        int is_sorted = 1;
        for(int j = 1; j <= i; j++)
        {
            int res = cmp(*(tab + j - 1), *(tab + j), cols);
            if(res == 2)
                return 1;
            if(res == 1)
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

int sort_rows(int **tab, int cols, int rows, int (*cmp)(const int *, const int *, int))
{
    if(tab == NULL || cols <= 0 || rows <= 0 || cmp == NULL)
        return 1;
    return bubble_sort(tab, cols, rows, cmp);
}