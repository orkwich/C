#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe: ");
    int number = 0;
    scanf("%d", &number);
    printf("%d\n%d", number, number * 10);
    return 0;
}