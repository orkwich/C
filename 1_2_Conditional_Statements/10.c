#include <stdio.h>

int main(void)
{
    printf("Wprowadz x\n");
    float number1 = 0;
    if(scanf("%f", &number1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Wprowadz y\n");
    float number2 = 0;
    if(scanf("%f", &number2) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("suma = %f\nroznica = %f\niloczyn = %f\n", number1 + number2, number1 - number2, number1 * number2);
    if(number2 != 0)
        printf("iloraz = %f", number1 / number2);
    else
        printf("Operation not permitted");
    return 0;
}