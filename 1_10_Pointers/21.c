#include <stdio.h>
#define WIDTH 5
#define HEIGHT 5

int column_statistics(const int *ptr, int width, int height, int column_id, int* max, int* min, float *avg)
{
    if(ptr == NULL || max == NULL || min == NULL || avg == NULL || column_id >= width || column_id < 0 || height <= 0 || width <= 0)
        return 1;
    int sum = 0;
    *max = *(ptr + column_id);
    *min = *(ptr + column_id);
    for(int j = 0; j < height; j++)
    {
        if(*max < *(ptr + column_id + (width * j)))
            *max = *(ptr + column_id + (width * j));
        if(*min > *(ptr + column_id + (width * j)))
            *min = *(ptr + column_id + (width * j));
        sum += *(ptr + column_id + (width * j));
    }
    *avg = (float) sum / height;
    return 0;
}

int row_statistics(const int *ptr, int width, int height, int row_id, int* max, int* min, float *avg)
{
    if(ptr == NULL || max == NULL || min == NULL || avg == NULL || row_id >= height || row_id < 0 || height <= 0 || width <= 0)
        return 1;
    int sum = 0;
    *max = *(ptr + (width * row_id));
    *min = *(ptr + (width * row_id));
    for(int j = 0; j < width; j++)
    {
        if(*max < *(ptr + j + (width * row_id)))
            *max = *(ptr + j + (width * row_id));
        if(*min > *(ptr + j + (width * row_id)))
            *min = *(ptr + j + (width * row_id));
        sum += *(ptr + j + (width * row_id));
    }
    *avg = (float) sum / width;
    return 0;
}

int main(void)
{
    printf("Podaj liczby:\n");
    int tab[HEIGHT][WIDTH];
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            if(scanf("%d", *(tab + i) + j) != 1)
            {
                printf("Incorrect input");
                return 1;
            }
    int max = 0;
    int min = 0;
    float avg = 0;
    for(int i = 0; i < WIDTH; i++)
    {
        column_statistics((int*)tab, WIDTH, HEIGHT, i, &max, &min, &avg);
        printf("%d %d %.2f\n", min, max, avg);
    }
    for(int i = 0; i < HEIGHT; i++)
    {
        row_statistics((int*)tab, WIDTH, HEIGHT, i, &max, &min, &avg);
        printf("%d %d %.2f\n", min, max, avg);
    }
    return 0;
}