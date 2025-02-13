#include <stdio.h>
#include "functions.h"

int main(void)
{
    printf("Enter data type: ");
    int type = 0;
    if(scanf("%d", &type) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(type == 1)
    {
        printf("Enter numbers: ");
        float a = 0;
        float b = 0;
        if(scanf("%f %f", &a, &b) != 2)
        {
            printf("Incorrect input");
            return 1;
        }
        printf("%f\n", SQR(a));
        printf("%f\n", SQR(b));
        printf("%f\n", MAX(a, b));
        printf("%f\n", MIN(a, b));
    } else if(type == 0)
    {
        printf("Enter numbers: ");
        int a = 0;
        int b = 0;
        if(scanf("%d %d", &a, &b) != 2)
        {
            printf("Incorrect input");
            return 1;
        }
        printf("%d\n", SQR(a));
        printf("%d\n", SQR(b));
        printf("%d\n", MAX(a, b));
        printf("%d\n", MIN(a, b));
    } else
    {
        printf("Incorrect input data");
        return 2;
    }
    return 0;
}