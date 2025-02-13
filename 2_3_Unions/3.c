#include <stdio.h>
#include "bit_set.h"

int main(void)
{
    printf("Podaj liczbe: ");
    union bit_set b;
    if(scanf("%hhu", &(b.byte)) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("%d ", (int)b.bits.bit8);
    printf("%d ", (int)b.bits.bit7);
    printf("%d ", (int)b.bits.bit6);
    printf("%d ", (int)b.bits.bit5);
    printf("%d ", (int)b.bits.bit4);
    printf("%d ", (int)b.bits.bit3);
    printf("%d ", (int)b.bits.bit2);
    printf("%d\n", (int)b.bits.bit1);
    return 0;
}