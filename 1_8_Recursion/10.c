#include <stdio.h>

int sum_of_digits(long long number)
{
    if(number < 0)
        number *= -1;
    if(number == 0)
        return 0;
    int sum = number % 10;
    return sum + sum_of_digits(number / 10);
}

int main(void)
{
    printf("Podaj liczbe: ");
    long long number;
    if(scanf("%lld", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Wynik: %d\n", sum_of_digits(number));
    return 0;
}