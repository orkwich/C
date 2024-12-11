#include <stdio.h>

int main(void)
{
    printf("Podaj min: ");
    int min = 0;
    if(scanf("%d", &min) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj max: ");
    int max = 0;
    if(scanf("%d", &max) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(min > max)
    {
        printf("Incorrect range");
        return 2;
    }
    for(; min <= max; min++)
        printf("%d ", min);
    return 0;
}