#include <stdio.h>

int main(void)
{
    unsigned long long int i = 1;
    for(int j = 0; j < 20; i *= 10, j++)
        printf("%llu ", i);
    return 0;
}