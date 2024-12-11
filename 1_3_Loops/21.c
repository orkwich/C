#include <stdio.h>

int main(void)
{
    printf("Podaj min: ");
    float min = 0;
    if(scanf("%f", &min) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj max: ");
    float max = 0;
    if(scanf("%f", &max) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(min > max)
    {
        printf("Incorrect range");
        return 2;
    }
    for(; min <= max; min += 0.25)
        printf("%f ", min);
    return 0;
}