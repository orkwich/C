#include <stdio.h>

// Program decoding instruction for this task

union bit_set
{
    unsigned char byte;
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
    } bits;
};

void decode(FILE *f)
{
    int bytes_count = 0;
    union bit_set b;
    union bit_set answer;
    FILE *out = fopen("zad12.txt", "w");
    while(fscanf(f, "%hhu", &(b.byte)) != EOF)
    {
        bytes_count++;
        if(bytes_count % 8 == 1)
            answer.bits.bit8 = b.bits.bit1;
        if(bytes_count % 8 == 2)
            answer.bits.bit7 = b.bits.bit1;
        if(bytes_count % 8 == 3)
            answer.bits.bit6 = b.bits.bit1;
        if(bytes_count % 8 == 4)
            answer.bits.bit5 = b.bits.bit1;
        if(bytes_count % 8 == 5)
            answer.bits.bit4 = b.bits.bit1;
        if(bytes_count % 8 == 6)
            answer.bits.bit3 = b.bits.bit1;
        if(bytes_count % 8 == 7)
            answer.bits.bit2 = b.bits.bit1;
        if(bytes_count % 8 == 0)
        {
            answer.bits.bit1 = b.bits.bit1;
            printf("%c", (char)answer.byte);
            fprintf(out, "%c", (char)answer.byte);
        }
    }
    fclose(out);
}

int main(void)
{
    FILE *f = fopen("zad", "r");
    decode(f);
    fclose(f);
    return 0;
}