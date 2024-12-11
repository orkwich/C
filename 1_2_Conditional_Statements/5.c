#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe: ");
    int number = 0;
    if(!(scanf("%d", &number)))
    {
        printf("Incorrect input");
        return 1;
    }
    if(number) printf("Not equal to zero");
    else printf("Equal to zero");    
    return 0;
}