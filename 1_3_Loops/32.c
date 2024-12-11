#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int absoluteValue(int number)
{
    if(number < 0)
        return -number;
    return number;
}

int main(void)
{
    srand(time(NULL));
    int result = 0;
    for(int i = 0; i < 100; i++)
        if(absoluteValue(rand() % 2001 - 1000) <= 100)
            result++;
    printf("%d\n", result);
    return 0;
}