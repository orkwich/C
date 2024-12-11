#include <stdio.h>

int main(void)
{
    for(int i = 0; i <= 100; i++)
        if((i >= 10 && i < 15) || (i >= 40 && i <=60) || (i > 70 && i < 80))
            printf("*%d\n", i);
        else
            printf("%d\n", i);
    return 0;
}