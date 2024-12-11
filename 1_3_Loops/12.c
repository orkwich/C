#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe: ");
    int number = 0;
    if(scanf("%d", &number) != 1 || number < 0 || number > 20)
    {
        printf("Incorrect input");
        return 1;
    }
    if(number == 0)
        printf("%d", 1);
    else
    {
        unsigned long long strong = 1;
        for(int i = 2; i <= number; i++)
            strong *= i;
        printf("%llu", strong);
    }
    return 0;
}