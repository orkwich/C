#include <stdio.h>

int isPrime(int number)
{
    if(number <= 0 || number == 1)
        return 0;
    for(int i = 2; i <= number / i; i++)
        if(number % i == 0 && number != i)
            return 0;
    return 1;
}

int main(void)
{
    int numbers[10];
    printf("Podaj liczby: ");
    for(int i = 0; i < 10; i+=2)
    {
        if(scanf("%d %d", &numbers[i], &numbers[i+1]) != 2)
        {
            printf("Input data type error\n");
            return 1;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        if(isPrime(numbers[i]))
            printf("%d prime\n", numbers[i]);
        else if(numbers[i] == 0 || numbers[i] == 1 || numbers[i] < 0)
            printf("%d other\n", numbers[i]);
        else
            printf("%d composite\n", numbers[i]);
    }

    return 0;
}