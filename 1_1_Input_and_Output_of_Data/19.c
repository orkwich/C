#include <stdio.h>

int main(void)
{
    printf("podaj liczbe: ");
    float number = 0;
    scanf("%f", &number);
    printf("wartosc funkcji y=%f", 2 * number * number * number - 4 * number * number + 3 * number - 7);
    return 0;
}