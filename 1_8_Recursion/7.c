#include <stdio.h>

int GCD(int a, int b)
{
    if(a < 0)
        a = -a;
    if(b < 0)
        b = -b;
    if(b == 0)
        return a;
    if(b > 1)
        return GCD(b, a % b);
    return b;
}

int main(void)
{
    printf("Podaj a: ");
    int a = 0;
    if(scanf("%d", &a) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj b: ");
    int b = 0;
    if(scanf("%d", &b) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("%d", GCD(a, b));    
    return 0;
}