#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include "vector_utils.h"

#define SIZE 50

enum direction
{
    ASCENDING = 1,
    DESCENDING = 2
};

int selection_sort_asc(int tab[], int size);
int selection_sort_desc(int tab[], int size);
int selection_sort(int tab[], int size, enum direction dir);

#endif