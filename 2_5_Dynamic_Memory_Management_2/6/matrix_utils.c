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

struct matrix_t* matrix_load_b(const char *filename, int *err_code)
{
    if(filename == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "rb");
    if(f == NULL)
    {
        if(err_code != NULL)
            *err_code = 2;
        return NULL;
    }
    int width = 0;
    if(fread(&width, sizeof(int), 1, f) != 1)
    {
        if(err_code != NULL)
            *err_code = 3;
        fclose(f);
        return NULL;
    }
    int height = 0;
    if(fread(&height, sizeof(int), 1, f) != 1)
    {
        if(err_code != NULL)
            *err_code = 3;
        fclose(f);
        return NULL;
    }
    if(width <= 0 || height <= 0)
    {
        if(err_code != NULL)
            *err_code = 3;
        fclose(f);
        return NULL;
    }
    struct matrix_t *m = matrix_create_struct(width, height);
    if(m == NULL)
    {
        if(err_code != NULL)
            *err_code = 4;
        fclose(f);
        return NULL;
    }
    for(int i = 0; i < m->height; i++)
    {
        if((int)fread(*(m->ptr + i), sizeof(int), m->width, f) != m->width)
        {
            if(err_code != NULL)
                *err_code = 3;
            fclose(f);
            matrix_destroy_struct(&m);
            return NULL;
        }
    }
    fclose(f);
    if(err_code != NULL)
        *err_code = 0;
    return m;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code)
{
    if(filename == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "r");
    if(f == NULL)
    {
        if(err_code != NULL)
            *err_code = 2;
        return NULL;
    }
    int width = 0;
    int height = 0;
    if(fscanf(f, "%d %d\n", &width, &height) != 2)
    {
        if(err_code != NULL)
            *err_code = 3;
        fclose(f);
        return NULL;
    }
    if(width <= 0 || height <= 0)
    {
        if(err_code != NULL)
            *err_code = 3;
        fclose(f);
        return NULL;
    }
    struct matrix_t *m = matrix_create_struct(width, height);
    if(m == NULL)
    {
        if(err_code != NULL)
            *err_code = 4;
        fclose(f);
        return NULL;
    }
    for(int i = 0; i < m->height; i++)
    {
        for(int j = 0; j < m->width; j++)
        {
            if(fscanf(f, "%d", *(m->ptr + i) + j) != 1)
            {
                if(err_code != NULL)
                    *err_code = 3;
                fclose(f);
                matrix_destroy_struct(&m);
                return NULL;
            }
        }
    }
    fclose(f);
    if(err_code != NULL)
        *err_code = 0;
    return m;
}

struct matrix_t* matrix_copy(const struct matrix_t *copy)
{
    if(copy == NULL || copy->ptr == NULL || copy->height <= 0 || copy->width <= 0)
        return NULL;
    struct matrix_t *m = matrix_create_struct(copy->width, copy->height);
    if(m == NULL)
        return NULL;
    for(int i = 0; i < copy->height; i++)
        for(int j = 0; j < copy->width; j++)
            *(*(m->ptr + i) + j) = *(*(copy->ptr + i) + j);
    return m;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <=0 || m2 == NULL || m2->ptr == NULL || m2->height <= 0 || m2->width <=0)
        return NULL;
    if(m1->height != m2->height || m1->width != m2->width)
        return NULL;
    struct matrix_t *m = matrix_create_struct(m1->width, m1->height);
    if(m == NULL)
        return NULL;
    for(int i = 0; i < m1->height; i++)
        for(int j = 0; j < m1->width; j++)
            *((*(m->ptr + i)) + j) = *((*(m1->ptr + i)) + j) + *((*(m2->ptr + i)) + j);
    return m;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <=0 || m2 == NULL || m2->ptr == NULL || m2->height <= 0 || m2->width <=0)
        return NULL;
    if(m1->height != m2->height || m1->width != m2->width)
        return NULL;
    struct matrix_t *m = matrix_create_struct(m1->width, m1->height);
    if(m == NULL)
        return NULL;
    for(int i = 0; i < m1->height; i++)
        for(int j = 0; j < m1->width; j++)
            *((*(m->ptr + i)) + j) = *((*(m1->ptr + i)) + j) - *((*(m2->ptr + i)) + j);
    return m;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <=0 || m2 == NULL || m2->ptr == NULL || m2->height <= 0 || m2->width <=0)
        return NULL;
    if(m1->height != m2->width || m1->width != m2->height)
        return NULL;
    struct matrix_t *m = matrix_create_struct(m1->height, m2->width);
    if(m == NULL)
        return NULL;
    for(int i = 0; i < m->height; i++)
        for(int j = 0; j < m->width; j++)
        {
            int val = 0;
            for(int k = 0; k < m1->width; k++)
                val += *(*(m1->ptr + i) + k) * *(*(m2->ptr + k) + j);
            *((*(m->ptr + i)) + j) = val;
        }
    return m;
}