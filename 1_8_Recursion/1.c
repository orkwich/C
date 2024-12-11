#include <stdio.h>

unsigned long factorial_rec(int n)
{
    if(n == 0 || n == 1)
        return 1;
    if(n > 0)
        return n * factorial_rec(n - 1);
    return 0;
}

int main(void)
{
    printf("Podaj n: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n < 0 || n > 20)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %lu\n", factorial_rec(n));
    return 0;
}