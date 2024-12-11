#include <stdio.h>

int main(void)
{
    float sum = 0;
    for(int i = 1; i <= 10; i++)
    {
        printf("Podaj %d liczbe: ", i);
        float tmp;
        if(scanf("%f", &tmp) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        sum += tmp;
    }
    printf("%f", sum);
    return 0;
}