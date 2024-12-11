#include <stdio.h>

int main(void)
{
    int numbers[11];
    for(int i = 0; i < 11; i++)
        numbers[i] = i;
    for(int i = 0; i < 11; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    return 0;
}