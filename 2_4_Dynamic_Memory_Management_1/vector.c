#include "vector.h"

int vector_create(struct vector_t *a, int N)
{
    if(a == NULL || N <= 0)
        return 1;
    a->ptr = malloc(sizeof(int) * N);
    if(a->ptr == NULL)
        return 2;
    a->capacity = N;
    a->size = 0;
    return 0;
}

int vector_create_struct(struct vector_t **a, int N)
{
    if(a == NULL || N <= 0)
        return 1;
    *a = malloc(sizeof(struct vector_t));
    if(*a == NULL)
        return 2;
    if(vector_create(*a, N) == 2)
    {
        free(*a);
        return 2;
    }
    return 0;
}

void vector_destroy(struct vector_t *a)
{
    if(a == NULL || a->ptr == NULL)
        return;
    free(a->ptr);
}

void vector_destroy_struct(struct vector_t **a)
{
    if(a == NULL || *a == NULL)
        return;
    vector_destroy(*a);
    free(*a);
}

void vector_display(const struct vector_t *a)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size <= 0 || a->size > a->capacity)
        return;
    for(int i = 0; i < a->size; i++)
        printf("%d ", *(a->ptr + i));
    printf("\n");
}

int vector_push_back(struct vector_t *a, int value)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity)
        return 1;
    if(a->size == a->capacity)
    {
        int *tmp = realloc(a->ptr, sizeof(int) * a->capacity * 2);
        if(tmp == NULL)
            return 2;
        a->ptr = tmp;
        a->capacity *= 2;
    }
    *(a->ptr + a->size++) = value;
    return 0;
}

void elem_erase(struct vector_t *v, int idx)
{
    for(int i = idx; i < v->size - 1; i++)
        *(v->ptr + i) = *(v->ptr + i + 1);
    v->size--;
}

int vector_erase(struct vector_t *a, int value)
{
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity)
        return -1;
    int count = 0;
    for(int i = 0; i < a->size; i++)
        if(*(a->ptr + i) == value)
        {
            elem_erase(a, i);
            i--;
            count++;
        }
    if((float)a->size < (float)a->capacity * 0.25 && a->capacity > 1)
    {
        int *tmp = realloc(a->ptr, sizeof(int) * ( a->capacity / 2));
        if(tmp != NULL)
        {
            a->ptr = tmp;
            a->capacity /= 2;
        }
    }
    return count;
}