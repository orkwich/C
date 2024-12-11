#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe z zakresu 0-10: ");
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(number < 0 || number >10)
    {
        printf("Incorrect input data");
        return 2;
    }

    if(number == 0)
        printf("zero");
    if(number == 1)
        printf("jeden");
    if(number == 2)
        printf("dwa");
    if(number == 3)
        printf("trzy");
    if(number == 4)
        printf("cztery");
    if(number == 5)
        printf("piec");
    if(number == 6)
        printf("szesc");
    if(number == 7)
        printf("siedem");
    if(number == 8)
        printf("osiem");
    if(number == 9)
        printf("dziewiec");
    if(number == 10)
        printf("dziesiec");
    
    return 0;
}