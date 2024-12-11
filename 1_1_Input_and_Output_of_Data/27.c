#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe zespolona: ");
    int realPart = 0;
    int imaginaryPart = 0;
    char sign = '\0';
    int output = scanf("%d%ci%d",&realPart, &sign, &imaginaryPart);
    printf("%d%c%di\n%d", realPart, sign, imaginaryPart, output);
    return 0;
}