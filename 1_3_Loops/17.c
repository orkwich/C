#include <stdio.h>

float absoluteValue(float number)
{
    if(number < 0) return -number;
    return number;
}

int main(void)
{
    printf("Podaj 10 liczb:\n");
    float sum = 0;
    for(int i = 0; i < 10; i++)
    {
        float number = 0;
        if(scanf("%f", &number) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        sum += absoluteValue(number);
    }
    printf("%.2f", sum);
    return 0;
}