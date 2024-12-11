#include <stdio.h>

int main(void)
{
    printf("Podaj liczby: ");
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;
    scanf("%d %d %d", &number1, &number2, &number3);
    int result = 0;
    result += number1 >= number2;
    result += number1 >= number3;
    printf("Wynik: %d", result);
    return 0;
}