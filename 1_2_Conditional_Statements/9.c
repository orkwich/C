#include <stdio.h>

int main(void)
{
    printf("Wprowadz x\n");
    int number1 = 0;
    if(scanf("%d", &number1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Wprowadz y\n");
    int number2 = 0;
    if(scanf("%d", &number2) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("suma = %d\nroznica = %d\niloczyn = %d\n", number1 + number2, number1 - number2, number1 * number2);
    if(number2 != 0)
        printf("iloraz = %d", number1 / number2);
    else
        printf("Operation not permitted");
    return 0;
}