#include <stdio.h>

int main(void)
{
    printf("Podaj liczby: ");
    int number1 = 0;
    int number2 = 0;
    switch(scanf("%d %d", &number1, &number2))
    {
        case 2:
            break;
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }
    printf("Podaj sybmbol operacji: ");
    char operation = '\0';
    getchar();
    scanf("%c", &operation);

    switch(operation == '/' && number2 == 0)
    {
        case 1:
        {
            printf("Illegal operation");
            return 2;
        }
    }

    switch(operation)
    {
        case '+':
        {
            int result = number1 + number2;
            printf("%d", result);
            break;
        }
        case '-':
        {
            int result = number1 - number2;
            printf("%d", result);
            break;
        }
        case '*':
        {
            int result = number1 * number2;
            printf("%d", result);
            break;
        }
        case '/':
        {
            float result = (float) number1 / number2;
            printf("%0.2f", result);
            break;
        }
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    return 0;
}