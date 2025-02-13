#include <stdio.h>

union set_bit
{
    unsigned int x;
    struct
    {
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
        unsigned char bit8 : 1;
    } bits[sizeof(unsigned int)];
};

int main(void)
{
    printf("Podaj liczbe: ");
    union set_bit b;
    b.x = 0;
    if(scanf("%u", &(b.x)) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    int count = 0;
    for(int i = 0; i < (int)sizeof(b.x); i++)
    {
        count += (b.bits + i)->bit1;
        count += (b.bits + i)->bit2;
        count += (b.bits + i)->bit3;
        count += (b.bits + i)->bit4;
        count += (b.bits + i)->bit5;
        count += (b.bits + i)->bit6;
        count += (b.bits + i)->bit7;
        count += (b.bits + i)->bit8;
    }
    if(!(count % 2))
        printf("YES");
    else
        printf("NO");
    return 0;
}