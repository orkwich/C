#include <stdio.h>

int main(void)
{
    for(int a = -10; a <= 10; a++)
        for(int b = -10; b <= 10; b++)
            if((a + b) * (a - b) == (a * a) + (b * b))
                printf("%d %d\n", a, b);
    return 0;
}