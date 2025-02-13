#include "functions.h"

int main(void)
{
    printf("Enter data type: ");
    int type = 0;
    if(scanf("%d", &type) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(type < 0 || type > 2)
    {
        printf("Incorrect input data");
        return 2;
    }
    int set_count;
    int clear_count;
    printf("Enter an integer number: ");
    if(type == 0)
    {
        unsigned int n = 0;
        if(scanf("%u", &n) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(n, &set_count, &clear_count);
        printf("%d\n%d\n", set_count, clear_count);
        DISPLAY_BITS(n);
        printf("\n");
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    }
    if(type == 1)
    {
        unsigned short n = 0;
        if(scanf("%hu", &n) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(n, &set_count, &clear_count);
        printf("%d\n%d\n", set_count, clear_count);
        DISPLAY_BITS(n);
        printf("\n");
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    }
    if(type == 2)
    {
        unsigned long long n = 0;
        if(scanf("%llu", &n) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(n, &set_count, &clear_count);
        printf("%d\n%d\n", set_count, clear_count);
        DISPLAY_BITS(n);
        printf("\n");
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    }
    return 0;
}