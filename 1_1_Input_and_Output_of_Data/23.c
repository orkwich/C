#include <stdio.h>

int main(void)
{
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;

    printf("Podaj liczby: ");
    scanf("%3d%3d%3d", &number1, &number2, &number3);
    printf("%03d\n%03d\n%03d\n", number1, number2, number3);

    return 0;
}