#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int randNumber = 0;
    while(randNumber < 100 || randNumber > 200)
    {
        randNumber = (rand() % 2001) - 1000;
        printf("%d\n", randNumber);
    }
    return 0;
}