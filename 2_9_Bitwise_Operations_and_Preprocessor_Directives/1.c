#include <stdio.h>
#include <stdint.h>

int is_equal(int a, int b)
{
    return !(a ^ b);
}

int is_negative(int value)
{
    uint32_t tmp = value;
    return tmp >> 31;
}

int main()
{
    printf("Podaj dwie liczby:\n");
    int a;
    int b;
    if(!is_equal(scanf("%d %d", &a, &b), 2))
    {
        printf("Incorrect input");
        return 1;
    }
    if(is_equal(a, b))
        printf("rowne\n");
    else
        printf("nierowne\n");
    if(is_negative(a))
        printf("ujemna ");
    else
        printf("nieujemna ");
    if(is_negative(b))
        printf("ujemna\n");
    else
        printf("nieujemna\n");
    return 0;
}
