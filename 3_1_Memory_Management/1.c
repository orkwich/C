#include <stdio.h>

int sum_short_int_int(const void * const in1, const void * const in2, void *out)
{
    if(in1 == NULL || in2 == NULL || out == NULL)
        return 1;
    *(int*)out = *(short*)in1 + *(int*)in2;
    return 0;
}

int main()
{
    short x = 5;
    int y = 6;
    int out;
    sum_short_int_int((void*)&x, (void*)&y, (void*)&out);
    printf("%d\n", out);
    return 0;
}