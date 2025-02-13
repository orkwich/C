#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int stats(int *sum, float *avg, int num,...)
{
    if(sum == NULL || avg == NULL || num <= 0)
        return 1;
    va_list args;
    va_start(args, num);
    (*sum) = 0;
    for(int i = 0; i < num; i++)
        (*sum) += va_arg(args, int);
    va_end(args);
    (*avg) = (float)(*sum) / num;
    return 0;
}

int main(void)
{
    printf("Enter number of elements: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n <= 0 || n > 3)
    {
        printf("Incorrect input data");
        return 2;
    }
    int arr[3];
    printf("Enter numbers: ");
    for(int i = 0; i < n; i++)
        if(scanf("%d", arr + i) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
    int sum = 0;
    float avg = 0;
    stats(&sum, &avg, n, *(arr), *(arr + 1), *(arr + 2));
    printf("%d %f\n", sum, avg);
    return 0;
}