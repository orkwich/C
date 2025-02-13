#include "matrix_utils.h"

int matrix_create(struct matrix_t *m, int width, int height)
{
    if(m == NULL || width <= 0 || height <= 0)
        return 1;
    m->ptr = malloc(sizeof(int*) * height);
    if(m->ptr == NULL)
    {
        free(m->ptr);
        return 2;
    }
    for(int i = 0; i < height; i++)
    {
        *(m->ptr + i) = malloc(sizeof(int) * width);
        if(*(m->ptr + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*(m->ptr + i));
            free(m->ptr);
            return 2;
        }
    }
    m->height = height;
    m->width = width;
    return 0;
}

struct matrix_t* matrix_create_struct(int width, int height)
{
    if(width <= 0 || height <= 0)
        return NULL;
    struct matrix_t *m = malloc(sizeof(struct matrix_t));
    if(m == NULL)
        return NULL;
    if(matrix_create(m, width, height) == 2)
    {
        free(m);
        return NULL;
    }
    return m;
}

int matrix_read(struct matrix_t *m)
{
    if(m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL)
        return 1;
    for(int i = 0; i < m->height; i++)
    {
        for(int j = 0; j < m->width; j++)
            if(scanf("%d", (*(m->ptr + i)) + j) != 1)
                return 2;
    }
    return 0;
}

void matrix_display(const struct matrix_t *m)
{
    if(m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL)
        return;
    for(int i = 0; i < m->height; i++)
    {
        for(int j = 0; j < m->width; j++)
            printf("%d ", *((*(m->ptr + i)) + j));
        printf("\n");
    }
}

void matrix_destroy(struct matrix_t *m)
{
    if(m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0)
        return;
    for(int i = 0; i < m->height; i++)
        free(*(m->ptr + i));
    free(m->ptr);
}

void matrix_destroy_struct(struct matrix_t **m)
{
    if(m == NULL)
        return;
    matrix_destroy(*m);
    free(*m);
    *m = NULL;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m)
{
    if(m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0)
        return NULL;
    struct matrix_t *mt = matrix_create_struct(m->height, m->width);
    if(mt == NULL)
        return NULL;
    for(int i = 0; i < m->width; i++)
    {
        for(int j = 0; j < m->height; j++)
        {
            *((*(mt->ptr + i)) + j) = *((*(m->ptr + j)) + i);
        }
    }
    return mt;
}

int matrix_save_b(const struct matrix_t *m, const char *filename)
{
    if(m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0 || filename == NULL)
        return 1;
    FILE *f = fopen(filename, "wb");
    if(f == NULL)
        return 2;
    if(fwrite(&m->width, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 3;
    }
    if(fwrite(&m->height, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 3;
    }
    for(int i = 0; i < m->height; i++)
        if((int)fwrite(*(m->ptr + i), sizeof(int), m->width, f) != m->width)
        {
            fclose(f);
            return 3;
        }
    fclose(f);
    return 0;
}

int matrix_save_t(const struct matrix_t *m, const char *filename)
{
    if(m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0 || filename == NULL)
        return 1;
    FILE *f = fopen(filename, "w");
    if(f == NULL)
        return 2;
    if(fprintf(f, "%d %d\n", m->width, m->height) < 0)
    {
        fclose(f);
        return 3;
    }
    for(int i = 0; i < m->height; i++)
    {
        for(int j = 0; j < m->width; j++)
            if(fprintf(f, "%d ", *((*(m->ptr + i)) + j)) < 0)
            {
                fclose(f);
                return 3;
            }
        if(fprintf(f, "\n") < 0)
        {
            fclose(f);
            return 3;
        }
    }
    fclose(f);
    return 0;
}