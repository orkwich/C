#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe zespolona: ");
    int real;
    int imaginary;
    char sign;

    if(scanf("%d%ci%d", &real, &sign, &imaginary) != 3 || (sign != '-' && sign != '+') || imaginary < 0)
    {
        printf("Incorrect input");
        return 1;
    }

    if(sign == '-') imaginary *= -1;

    printf("Czesc rzeczywista: %d\nCzesc urojona: %d", real, imaginary);
    return 0;
}