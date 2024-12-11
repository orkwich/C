#include <stdio.h>

int main(void)
{
    printf("Podaj liczby:\n");
    float tmp = 0;
    float max = -__FLT_MAX__;
    float min = __FLT_MAX__;
    float sum = 0;
    int size = 0;
    while(tmp != -1)
    {
        if(scanf("%f", &tmp) != 1)
        {
            printf("Incorrect input");
            return 1;
        } else if(tmp != -1)
        {
            sum += tmp;
            size++;
            if(max < tmp)
                max = tmp;
            if(min > tmp)
                min = tmp;
        }
    }
    float average = sum / size;
    printf("%.2f\n%.2f\n%.2f\n", min, max, average);
    return 0;
}