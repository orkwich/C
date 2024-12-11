#include <stdio.h>

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int read_vector_double(double vec[], int size, double stop_value)
{
    if(size <= 0)
        return -1;
    int i = 0;
    while(size)
    {
        if(!scanf("%lf", vec))
            return -2;
        if(*vec == stop_value)
            break;
        vec++;
        i++;
        size--;
    }
    if(!i)
        return -1;
    return i;
}

double horner(double a[], double x, int n)
{
    if(n < 1)
        return -1;
    if(n == 1)
        return a[n - 1];
    return (horner(a, x, n - 1) * x) + a[n - 1];
}

int main(void)
{
    printf("podaj wspolczynniki wielomianu:\n");
    double vec[100];
    int size = read_vector_double(vec, 100, 0);
    if(size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    clear();
    printf("Podaj zmienna x:\n");
    double x = 0;
    if(scanf("%lf", &x) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("w=%.2lf", horner(vec, x, size));
    return 0;
}