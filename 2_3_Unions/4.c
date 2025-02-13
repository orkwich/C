#include <stdio.h>
#define WORD_SIZE 2
#define BYTES_SIZE 4

union bit_set
{
    unsigned int x;
    unsigned short words[WORD_SIZE];
    unsigned char bytes[BYTES_SIZE];
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
    } bits[BYTES_SIZE];
};

int main(void)
{
    printf("Podaj liczbe: ");
    union bit_set b;
    if(scanf("%u", &(b.x)) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("%u\n", b.x);
    for(int i = 0; i < WORD_SIZE; i++)
        printf("%d ", (int)*(b.words + i));
    printf("\n");
    for(int i = 0; i < BYTES_SIZE; i++)
        printf("%d ", (int)*(b.bytes + i));
    printf("\n");
    for(int i = 0; i < BYTES_SIZE; i++)
        printf("%d%d%d%d%d%d%d%d ", (int)(b.bits + i)->bit8, (int)(b.bits + i)->bit7, (int)(b.bits + i)->bit6, (int)(b.bits + i)->bit5, (int)(b.bits + i)->bit4, (int)(b.bits + i)->bit3, (int)(b.bits + i)->bit2, (int)(b.bits + i)->bit1);
    return 0;
}