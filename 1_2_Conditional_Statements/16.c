#include <stdio.h>

int main(void)
{
    printf("Podaj swoja licze: ");
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(!number)
        printf("zerowa");
    else if(number < 0)
        printf("ujemna");
    else
        printf("dodatnia");
    return 0;
}