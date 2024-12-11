#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int sum = 0;
    for(int i=0; i < 100; i++) sum += (rand() % 11) + 10;
    printf("%d\n", sum);
    return 0;
}