#include <stdio.h>

int main(void)
{
    printf("Wprowadz liczbe: ");
    double number = 0;
    scanf("%lf", &number);
    printf("Wprowadz dokladnosc: ");
    int precision = 0;
    scanf("%d", &precision);
    printf("%.*lf\n", precision, number);
    return 0;
}