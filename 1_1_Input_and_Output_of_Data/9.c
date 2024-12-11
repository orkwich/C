#include <stdio.h>

int main(void)
{
    int number1 = 21;
    int number2 = 37;
    printf("%d %d\n%d\n%.2lf\n%d\n%d", number1, number2, number1 * number2, (double)number1 / number2, number1 + number2, number1 - number2);

    return 0;
}