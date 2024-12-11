#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("podaj kwote poczotkowa: ");
    float amount = 0;
    if(scanf("%f", &amount) != 1 || amount < 0)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("podaj liczbe miesiecy: ");
    int months = 0;
    if(scanf("%d", &months) != 1 || months < 0)
    {
        printf("Incorrect input");
        return 1;
    }

    amount *= pow(1.01, months);
    printf("%.2f", amount);

    return 0;
}