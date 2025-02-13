#include <stdio.h>
#include "byte_set.h"

int main(void)
{
    printf("Podaj liczbe: ");
    union byte_set b;
    if(scanf("%d", &(b.x)) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    for(int i = 0; i < 4; i++)
        printf("%d ", (int)*(b.bytes + i));
    return 0;
}