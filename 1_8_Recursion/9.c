#include <stdio.h>

long long binary_exponentiation(long long a, unsigned int n)
{
    if(n == 0)
        return 1;
    if(n % 2)
        return a * binary_exponentiation(a * a, (n - 1) / 2);
    else
        return binary_exponentiation(a * a, n / 2);
}

int main(void)
{
    printf("Podaj podstawe: ");
    long long a = 0;
    if(scanf("%lld", &a) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj wykladnik: ");
    unsigned int n = 0;
    if(scanf("%u", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Wynik: %lld\n", binary_exponentiation(a, n));
    return 0;
}