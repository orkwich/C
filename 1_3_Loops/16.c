#include <stdio.h>

int main(void)
{
    float number1 = 0;
    float number2 = 1;
    printf("Podaj liczbe: ");
    while(scanf("%f", &number1) == 1)
    {
        number2 *= number1;
        printf("Wynik: %.2f\n", number2);
        printf("Podaj liczbe: ");
        getchar();
    }
    printf("Incorrect input");
    return 0;
}