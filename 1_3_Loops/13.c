#include <stdio.h>

int main(void)
{
    printf("Podaj kolejna liczbe: ");
    float number1 = 0;
    if(scanf("%f", &number1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(number1 == 0)
        return 0;
    do
    {
        printf("Podaj kolejna liczbe: ");
        float number2 = 0;
        if(scanf("%f", &number2) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        printf("%f\n", number2 - number1);
        number1 = number2;
    } while(number1 != 0);
    
    return 0;
}