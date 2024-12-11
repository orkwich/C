#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "types_utils.h"

int quicksort_asc(int l, int r, int tab[], int tabSize);
int quicksort_desc(int l, int r, int tab[], int tabSize);
int quicksort(int tab[], int size, enum direction dir);

#endif