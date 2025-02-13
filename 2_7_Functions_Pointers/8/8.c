#include "comparators.h"

int main(void)
{
    printf("Enter data type: ");
    int data_type = -1;
    if(scanf("%d", &data_type) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(data_type < 0 || data_type > 2)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Enter array size: ");
    int size = -1;
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    void *arr = NULL;
    if(data_type == 0)
        arr = malloc(sizeof(int) * size);
    if(data_type == 1)
        arr = malloc(sizeof(double) * size);
    if(data_type == 2)
        arr = malloc(sizeof(struct point_t) * size);
    if(arr == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    if(data_type == 0)
    {
        printf("Enter Ints: ");
        for(int i = 0; i < size; i++)
        {
            if(scanf("%d", ((int*)arr) + i) != 1)
            {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
        }
        sort(arr, size, sizeof(int), comp_int);
        for(int i = 0; i < size; i++)
            printf("%d ", *(((int*)arr) + i));
    }
    if(data_type == 1)
    {
        printf("Enter Ints: ");
        for(int i = 0; i < size; i++)
        {
            if(scanf("%lf", ((double*)arr) + i) != 1)
            {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
        }
        sort(arr, size, sizeof(double), comp_double);
        for(int i = 0; i < size; i++)
            printf("%lf ", *(((double*)arr) + i));
    }
    if(data_type == 2)
    {
        printf("Enter Ints: ");
        for(int i = 0; i < size; i++)
        {
            if(scanf("%lf %lf", &(((struct point_t*)arr) + i)->x, &(((struct point_t*)arr) + i)->y) != 2)
            {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
        }
        sort(arr, size, sizeof(struct point_t), comp_point);
        for(int i = 0; i < size; i++)
            printf("%lf %lf\n", (((struct point_t*)arr) + i)->x, (((struct point_t*)arr) + i)->y);
    }
    free(arr);
    return 0;
}