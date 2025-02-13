#include "image_utils.h"

struct image_t* create_img(char *type, int width, int height)
{
    if(type == NULL || width <= 0 || height <= 0)
        return NULL;
    struct image_t *img = malloc(sizeof(struct image_t));
    if(img == NULL)
        return NULL;
    img->ptr = malloc(sizeof(int*) * height);
    if(img->ptr == NULL)
    {
        free(img);
        return NULL;
    }
    for(int i = 0; i < height; i++)
    {
        *(img->ptr + i) = malloc(sizeof(int) * width);
        if(*(img->ptr + i) == NULL)
        {
            for(--i; i >= 0; i--)
                free(*(img->ptr + i));
            free(img->ptr);
            free(img);
            return NULL;
        }
    }
    strcpy(img->type, type);
    img->width = width;
    img->height = height;
    return img;
}

void destroy_image(struct image_t **m)
{
    if(m == NULL || *m == NULL)
        return;
    if((*m)->ptr == NULL || (*m)->height <= 0)
    {
        free(*m);
        *m = NULL;
        return;
    }
    for(int i = 0; i < (*m)->height; i++)
        free(*((*m)->ptr + i));
    free((*m)->ptr);
    free(*m);
    *m = NULL;
}

struct image_t* load_image_t(const char *filename, int *err_code)
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
    char *tmp_type = malloc(sizeof(char) * 3);
    if(tmp_type == NULL)
    {
        if(err_code != NULL)
            *err_code = 4;
        fclose(f);
        return NULL;
    }
    if(fscanf(f, "%2[P1-6]", tmp_type) != 1)
    {
        if(err_code != NULL)
            *err_code = 3;
        free(tmp_type);
        fclose(f);
        return NULL;
    }
    if(strcmp(tmp_type, "P2") != 0)
    {
        if(err_code != NULL)
            *err_code = 3;
        free(tmp_type);
        fclose(f);
        return NULL;
    }
    int width = 0;
    int height = 0;
    if(fscanf(f, "%d %d", &width, &height) != 2 || width <= 0 || height <= 0)
    {
        if(err_code != NULL)
            *err_code = 3;
        free(tmp_type);
        fclose(f);
        return NULL;
    }
    int grey_lvl = 0;
    if(fscanf(f, "%d", &grey_lvl) != 1)
    {
        if(err_code != NULL)
            *err_code = 3;
        free(tmp_type);
        fclose(f);
        return NULL;
    }
    struct image_t *img = create_img(tmp_type, width, height);
    free(tmp_type);
    if(img == NULL)
    {
        if(err_code != NULL)
            *err_code = 4;
        fclose(f);
        return NULL;
    }
    for(int i = 0; i < img->height; i++)
        for(int j = 0; j < img->width; j++)
            if(fscanf(f, "%d", *(img->ptr + i) + j) != 1 || *(*(img->ptr + i) + j) < 0 || *(*(img->ptr + i) + j) > grey_lvl)
            {
                if(err_code != NULL)
                    *err_code = 3;
                destroy_image(&img);
                fclose(f);
                return NULL;
            }
    fclose(f);
    if(err_code != NULL)
        *err_code = 0;
    return img;
}

int save_image_t(const char *filename, const struct image_t *m1)
{
    if(filename == NULL || m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0 || strcmp(m1->type, "P2") != 0)
        return 1;
    FILE *f = fopen(filename, "w");
    if(f == NULL)
        return 2;
    if(fprintf(f, "%2s\n", m1->type) < 0)
    {
        fclose(f);
        return 3;
    }
    if(fprintf(f, "%d %d\n%d\n", m1->width, m1->height, 255) < 0)
    {
        fclose(f);
        return 3;
    }
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
            if(fprintf(f, "%d ", *(*(m1->ptr + i) + j)) < 0)
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

const int* image_get_pixel(const struct image_t *img, int x, int y)
{
    if(img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || x < 0 || y < 0 || img->height <= y || img->width <= x)
        return NULL;
    return (const int*)*(img->ptr + y) + x;
}

int* image_set_pixel(struct image_t *img, int x, int y)
{
    if(img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || x < 0 || y < 0 || img->height <= y || img->width <= x)
        return NULL;
    return (int*)*(img->ptr + y) + x;
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty)
{
    if(img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || src == NULL || src->ptr == NULL || src->height <= 0 || src->width <= 0 || destx < 0 || desty < 0)
        return 1;
    if(img->height - desty < src->height || img->width - destx < src->width)
        return 1;
    for(int i = 0; i < src->height; i++)
        for(int j = 0; j < src->width; j++)
        {
            int *tmp_px = image_set_pixel(img, j + destx, i + desty);
            *tmp_px = *image_get_pixel(src, j, i);
        }
    return 0;
}