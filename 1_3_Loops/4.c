#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe: ");
    unsigned long long number;
    if(scanf("%llu", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    int last = number % 10;
    while(number >= 10)
        number = number / 10;
    printf("%llu\n%d\n", number, last);
    return 0;
}