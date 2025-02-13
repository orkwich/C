#ifndef COMPARATORS_H
#define COMPARATORS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point_t
{
	double x;
	double y;
};

int comp_int(const void *, const void *);
int comp_double(const void *, const void *);
int comp_point(const void *, const void *);
int sort(void *, int size, size_t elem_size, int (*)(const void *, const void *));

#endif