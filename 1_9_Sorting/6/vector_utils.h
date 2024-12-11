#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H
#define MAX_SIZE 50
#define STOP 0

#include <stdio.h>

void display_vector(const int vec[], int size);
int read_vector(int vec[], int size, int stop_value); //-2 for wrong input, -1 for no input or wrong tab size

#endif