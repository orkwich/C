#include <stdio.h>

int main(void)
{
    printf("Podaj liczby: ");
    int number1 = 0;
    int number2 = 0;
    scanf("%d %d",&number1, &number2);
    int difference = number1 - number2;
    int tmp = difference >> sizeof(int)*8-1;
    difference = (tmp + difference) ^ tmp; //absolute value of difference
    printf("Maximum: %d\nMinimum: %d",((number1+number2)+difference)/2,((number1+number2)-difference)/2);
    return 0;
}