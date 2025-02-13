#include <stdio.h>

unsigned int bit_val(unsigned int *pvalue, int n)
{
    return ((*pvalue) >> n) & ((unsigned int)1);
}

unsigned int swap_bits(unsigned int *pvalue, int b1, int b2)
{
    if(pvalue == NULL || b1 < 0 || b2 < 0 || b1 == b2 || b1 >= 32 || b2 >= 32)
        return 1;
    unsigned int b1_val = bit_val(pvalue, b1);
    unsigned int b2_val = bit_val(pvalue, b2);
    if(b1_val != b2_val)
    {
        if(b1_val)
            (*pvalue) = (*pvalue) & ~((unsigned int)1 << b1);
        else
            (*pvalue) = (*pvalue) | ((unsigned int)1 << b1);
        if(b2_val)
            (*pvalue) = (*pvalue) & ~((unsigned int)1 << b2);
        else
            (*pvalue) = (*pvalue) | ((unsigned int)1 << b2);
    }
    return 0;
}

int main(void)
{
    printf("Enter an uint32 number: ");
    unsigned int num = 0;
    if(scanf("%u", &num) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Enter 1st bit index: ");
    int b1 = 0;
    if(scanf("%d", &b1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Enter 2nd bit index: ");
    int b2 = 0;
    if(scanf("%d", &b2) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    swap_bits(&num, b1, b2);
    printf("Result: %u", num);
    return 0;
}