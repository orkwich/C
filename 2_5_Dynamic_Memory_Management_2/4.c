#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix_t{
  int **ptr;
  int width;
  int height;
};

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

int main(void)
{
    printf("Podaj wysokosc i szerokosc: ");
    int height = 0;
    int width = 0;
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(width <= 0 || height <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct matrix_t m;
    if(matrix_create(&m, width, height))
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartosci: ");
    if(matrix_read(&m) == 2)
    {
        printf("Incorrect input");
        matrix_destroy(&m);
        return 1;
    }
    matrix_display(&m);
    matrix_destroy(&m);
    return 0;
}