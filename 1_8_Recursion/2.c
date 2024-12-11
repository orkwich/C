#include <stdio.h>

long power_rec(int a, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return a;
    if(n > 0)
        return a * power_rec(a, n - 1);
    return 0;
}

int main(void)
{
    printf("Podaj a: ");
    int a = 0;
    if(scanf("%d", &a) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj n: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n < 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %ld\n", power_rec(a, n));
    return 0;
}