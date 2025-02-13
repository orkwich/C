#ifndef COMPARATORS_H
#define COMAPRATORS_H
#include <stdio.h>

int comp_min(const int *ptr1, const int *ptr2, int width);
int comp_max(const int *ptr1, const int *ptr2, int width);
int comp_sum(const int *ptr1, const int *ptr2, int width);
int sort_rows(int **tab, int cols, int rows, int (*)(const int *, const int *, int));

#endif