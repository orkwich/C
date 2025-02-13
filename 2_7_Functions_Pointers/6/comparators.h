#ifndef COMPARATORS_H
#define COMPARATORS_H
#include <stdio.h>

int comp_int(int a, int b);
int comp_int_abs(int a, int b);
int comp_int_length(int a, int b);
int comp_int_digits_sum(int a, int b);
int sort_int(int tab[], int size, int (*cmp)(int, int));

#endif