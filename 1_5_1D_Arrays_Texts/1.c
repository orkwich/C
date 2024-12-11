#include <stdio.h>

int main(void)
{
    int numbers[26];
    for(int i = 65; i <= 90; i++)
    {
        numbers[i - 65] = i;
        printf("%2d %1c %1c\n", numbers[i - 65], numbers[i - 65], numbers[i -65] + 32);
    }
    return 0;
}