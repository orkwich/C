#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_chicken(void);
void print_egg(void);
void print_rabbit(void);
void (**easter(int size, void (*chicken)(void), void (*egg)(void), void (*rabbit)(void)))(void);
#endif  