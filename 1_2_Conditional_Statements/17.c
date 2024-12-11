#include <stdio.h>

int main(void)
{
    printf("Podaj x\n");
    float number = 0;
    if(scanf("%f", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }

    float result;
    if(number < -5)
    {
        result = (number + 5) * (number + 5) - 10;
        printf("%f", result);
    }
    else if(number > 5)
    {
        result = ((number * 0.5) -2) * (2 - (number * 3 / 4));
        printf("%f", result);
    }
    else
    {
        result = (2 * number * number) + (3 * number) - 1;
        printf("%f", result);
    }
    
    return 0;
}