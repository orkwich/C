#include <stdio.h>

int main(void)
{
    float number1 = 21.37;
    float number2 = 4.2;
    printf("%f %f\n%f\n%.2f\n%f\n%f", number1, number2, number1 * number2, (float)number1 / number2, number1 + number2, number1 - number2);

    return 0;
}