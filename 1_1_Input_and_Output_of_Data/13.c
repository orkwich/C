#include <stdio.h>

int main(void)
{
    printf("Podaj pierwsza liczbe: ");
    int number1 = 0;
    scanf("%d", &number1);
    printf("Podaj druga liczbe: ");
    int number2 = 0;
    scanf("%d", &number2);

    printf("%d\n%d\n%d\n%d", number1 + number2, number1 - number2, number1 * number2, number1 / number2);
    
    return 0;
}