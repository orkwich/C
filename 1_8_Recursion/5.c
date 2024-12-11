#include <stdio.h>

int abs(int number)
{
    if(number < 0)
        return -number;
    return number;
}

int sum_digits(int number, int oddOrEven)
{
    if(number < 0)
        number *= -1;
    if(oddOrEven)
        number /= 10;
    if(number == 0)
        return 0;
    int sum = number % 10;
    return sum + sum_digits(number / 10, 1);
}

int is_divisible_by_11(int number)
{
    if(number < 0)
        number *= -1;
    if(number == 0)
        return 1;
    if(number < 11)
        return 0;
    int sumOdd = sum_digits(number, 0);
    int sumEven = sum_digits(number, 1);
    return is_divisible_by_11(abs(sumEven - sumOdd));
}

int main(void)
{
    printf("Podaj liczbe: ");
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(is_divisible_by_11(number))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}