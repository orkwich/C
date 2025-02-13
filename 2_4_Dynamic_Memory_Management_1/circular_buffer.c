#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if(a == NULL || N <= 0)
        return 1;
    a->ptr = malloc(sizeof(int) * N);
    if(a->ptr == NULL)
        return 2;
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if(cb == NULL || N <= 0)
        return 1;
    *cb = malloc(sizeof(struct circular_buffer_t));
    if(*cb == NULL)
        return 2;
    int err_code = circular_buffer_create(*cb, N);
    if(err_code == 2)
        free(*cb);
    return err_code;
}

void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL)
        return;
    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if(a == NULL)
        return;
    circular_buffer_destroy(*a);
    free(*a);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if(cb == NULL || cb->ptr == NULL || cb->capacity <= 0 || cb->end < 0 || cb->begin < 0 || cb->capacity <= cb->begin || cb->capacity <= cb->end)
        return 1;
    *(cb->ptr + cb->end++) = value;
    if(cb->end == cb->capacity)
        cb->end = 0;
    if(cb->full)
        cb->begin = cb->end;
    else if(cb->begin == cb->end)
        cb->full = 1;
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->capacity <= a->begin || a->capacity <= a->end)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 1;
    }
    if(a->begin == a->end && a->full == 0)
    {
        if(err_code != NULL)
            *err_code = 2;
        return 2;
    }
    int value = *(a->ptr + a->begin++);
    if(a->begin == a->capacity)
        a->begin = 0;
    if(a->full == 1)
        a->full = 0;
    if(err_code != NULL)
        *err_code = 0;
    return value;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->capacity <= a->begin || a->capacity <= a->end)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 1;
    }
    if(a->begin == a->end && a->full == 0)
    {
        if(err_code != NULL)
            *err_code = 2;
        return 2;
    }
    if(a->end > 0)
        a->end--;
    else
        a->end = a->capacity - 1;
    if(a->full == 1)
        a->full = 0;
    if(err_code != NULL)
        *err_code = 0;
    return *(a->ptr + a->end);
}

int circular_buffer_empty(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->capacity <= a->begin || a->capacity <= a->end)
        return -1;
    if(a->begin == a->end && a->full == 0)
        return 1;
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->capacity <= a->begin || a->capacity <= a->end)
        return -1;
    return a->full;
}

void circular_buffer_display(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->capacity <= a->begin || a->capacity <= a->end)
        return;
    if(a->full == 0 && a->begin == a->end)
        return;
    int tmp_idx = a->begin;
    do
    {
        printf("%d ", *(a->ptr + tmp_idx++));
        if(tmp_idx == a->capacity)
            tmp_idx = 0;
    } while(tmp_idx != a->end);
    printf("\n");
}