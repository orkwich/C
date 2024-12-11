#include <stdio.h>

int clamp(int x, int lo, int hi)
{
    if(x >= hi)
        return hi;
    if(x <= lo)
        return lo;
    return x;
}

int main(void)
{
    printf("Podaj pierwsza liczbe:");
    int x = 0;
    if(scanf("%d", &x) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj pierwsza granice: ");
    int lo = 0;
    if(scanf("%d", &lo) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj druga granice: ");
    int hi = 0;
    if(scanf("%d", &hi) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(hi < lo)
    {
        int tmp = hi;
        hi = lo;
        lo = tmp;
    }
    printf("%d\n", clamp(x, lo, hi));
    return 0;
}