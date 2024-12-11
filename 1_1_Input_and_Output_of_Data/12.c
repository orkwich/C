#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe: ");
    float number = 0;
    scanf("%f", &number);
    printf("%f\n%f", number, number * 10);
    return 0;
}