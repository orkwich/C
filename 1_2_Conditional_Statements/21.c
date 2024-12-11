#include <stdio.h>

int main(void)
{
    printf("Podaj pierwsza liczbe: ");
    int number1 = 0;
    if(scanf("%d", &number1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj druga liczbe: ");
    int number2 = 0;
    if(scanf("%d", &number2) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    char sign = '\0';
    getchar();
    printf("Podaj symbol operacji: ");
    if(scanf("%c", &sign) != 1 || (sign != '-' && sign != '+' && sign != '*' && sign != '/'))
    {
        printf("Incorrect input");
        return 1;
    }
    if(number2 == 0 && sign == '/')
    {
        printf("Operation not permitted");
        return 2;
    }
    if(sign == '-')
        printf("%d", number1 - number2);
    if(sign == '+')
        printf("%d", number1 + number2);
    if(sign == '*')
        printf("%d", number1 * number2);
    if(sign == '/')
        printf("%0.2f", (float)number1 / number2);
    return 0;
}