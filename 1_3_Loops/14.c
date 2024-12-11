#include <stdio.h>

int main(void)
{
    printf("Podaj liczby:\n");
    float tmp = 0;
    float max = -__FLT_MAX__;
    float min = __FLT_MAX__;
    float sum = 0;
    for(int i = 0; i < 100; i++)
    {
        if(scanf("%f", &tmp) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        sum += tmp;
        if(max < tmp)
            max = tmp;
        if(min > tmp)
            min = tmp;
    }
    float average = sum / 100;
    printf("%.2f\n%.2f\n%.2f\n", min, max, average);
    return 0;
}