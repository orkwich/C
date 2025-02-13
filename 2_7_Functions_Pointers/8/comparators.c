#include "comparators.h"

int comp_int(const void *a, const void *b)
{
    if(a == NULL || b == NULL)
        return 0;
    int tmp_a = *((int*)a);
    int tmp_b = *((int*)b);
    return -(tmp_a < tmp_b) + (tmp_a > tmp_b);
}

int comp_double(const void *a, const void *b)
{
    if(a == NULL || b == NULL)
        return 0;
    double tmp_a = *((double*)a);
    double tmp_b = *((double*)b);
    return -(tmp_a < tmp_b) + (tmp_a > tmp_b);
}

int comp_point(const void *a, const void *b)
{
    if(a == NULL || b == NULL)
        return 0;
    struct point_t *tmp_a = (struct point_t*)a;
    struct point_t *tmp_b = (struct point_t*)b;
    if(tmp_a->x == tmp_b->x)
        return -(tmp_a->y < tmp_b->y) + (tmp_a->y > tmp_b->y);
    return -(tmp_a->x < tmp_b->x) + (tmp_a->x > tmp_b->x);
}

void swap(void *ptr1, void *ptr2, size_t elem_size)
{
    void *tmp = malloc(elem_size);
    if(tmp == NULL)
        return;
    memcpy(tmp, ptr1, elem_size);
    memcpy(ptr1, ptr2, elem_size);
    memcpy(ptr2, tmp, elem_size);
    free(tmp);
}

int sort(void *tab, int size, size_t elem_size, int (*cmp)(const void *, const void *))
{
    if(size <= 0 || tab == NULL || elem_size == 0 || cmp == NULL)
        return 1;
    for(int i = size - 1; i >= 0; i--)
    {
        int is_sorted = 1;
        for(int j = 1; j <= i; j++)
        {
            void *cur_ptr1 = (((char*)tab) + (((j - 1) * elem_size)));
            void *cur_ptr2 = (((char*)tab) + (j * elem_size));
            if(cmp(cur_ptr1, cur_ptr2) > 0)
            {
                is_sorted = 0;
                swap(cur_ptr1, cur_ptr2, elem_size);
            }
        }
        if(is_sorted)
            return 0;
    }
    return 0;
}