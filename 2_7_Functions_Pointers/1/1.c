#include <stdio.h>
#include "int_operations.h"
#define OP_COUNT 4

int main(void)
{
    int (*operations[OP_COUNT])(int, int);
    *operations = &add_int;
    *(operations + 1) = &sub_int;
    *(operations + 2) = &div_int;
    *(operations + 3) = &mul_int;
    printf("Enter numbers: ");
    int a = 0;
    int b = 0;
    if(scanf("%d %d", &a, &b) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Choose an operation: ");
    int op = -1;
    if(scanf("%d", &op) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(op < 0 || op > 3)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Result: %d\n", calculate(a, b, *(operations + op)));
    return 0;
}