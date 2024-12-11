#include <stdio.h>

long int fibonacci(int n)
{
    if(n < 0)
        return -1;
    if(n == 0 || n == 1)
        return n + 1;
    return fibonacci(n - 1) + fibonacci(n - 2) + n;
}

int main(void)
{
    printf("Ktory wyraz ciagu fibonacciego chcesz wyznaczyc: ");
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
    printf("Wynik: %ld",fibonacci(n));
    return 0;
}