#include <stdio.h>

int main(void)
{
    printf("Podaj pierwsza liczbe: ");
    float number1 = 0;
    scanf("%f", &number1);
    printf("Podaj druga liczbe: ");
    float number2 = 0;
    scanf("%f", &number2);

    printf("%f\n%f\n%f\n%f", number1 + number2, number1 - number2, number1 * number2, number1 / number2);
    
    return 0;
}