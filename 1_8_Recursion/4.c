#include <stdio.h>

unsigned long sum_rec(int n)
{
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;
    return n + sum_rec(n - 1);
}

int main(void)
{
    printf("Podaj liczbe, dla ktorej chcesz policzyc sume: ");
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(number < 1)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %lu", sum_rec(number));
    return 0;
}