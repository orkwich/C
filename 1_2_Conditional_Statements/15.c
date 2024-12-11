#include <stdio.h>

int main(void)
{
    printf("Podaj a: ");
    float a = 0;
    if(scanf("%f", &a) != 1)
    {
        printf("Incorrect input");
        return 1;
    }

    printf("Podaj b: ");
    float b = 0;
    if(scanf("%f", &b) != 1)
    {
        printf("Incorrect input");
        return 1;
    }

    if((a + b) * (a - b) == a * a + b * b)
        printf("tozsamosc jest prawdziwa");
    else
        printf("tozsamosc nie jest prawdziwa");
    
    return 0;
}