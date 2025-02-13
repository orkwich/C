#ifndef INT_OPERATIONS_H
#define INT_OPERATIONS_H
#include <stdio.h>

enum operations_t
{
    op_add,
    op_sub,
    op_div,
    op_mul
};

int (*get_function(int op))(int, int);
int calculate(int a, int b, int (*operation)(int, int));
int add_int(int a, int b);
int sub_int(int a, int b);
int div_int(int a, int b);
int mul_int(int a, int b);

#endif