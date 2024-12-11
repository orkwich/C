#include <stdio.h>

int abs(int number)
{
    switch(number < 0)
    {
        case 1:
            return -number;
        default:
            return number;
    }
}

int main(void)
{
    printf("Podaj dwie liczby: ");
    int number1 = 0;
    int number2 = 0;
    int readOutput1 = scanf("%d", &number1);
    int readOutput2 = scanf("%d", &number2);

    switch(readOutput1 && readOutput2)
    {
        case 1:
        {
            int difference = abs(number1 - number2);
            printf("%d\n%d", ((number1 + number2) + difference) / 2, ((number1 + number2) - difference) / 2);
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