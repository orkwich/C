#include <stdio.h>
#include <math.h>

double value(int n) {return (double)1/(n*(n+1));}

int main(void)
{
    double eps = pow(10,-4);
    double sum = 0;
    int n = 1;
    while(value(n)>=eps) sum += value(n++);
    printf("%d %.4lf", --n, sum);
    return 0;
}