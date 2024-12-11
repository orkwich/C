#include <stdio.h>

int main(void)
{
    int numbers[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d %d %d %d %d %d %d %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9], numbers[10]);
    for(int i = 0; i < 11; i++)
        printf("%d\n", numbers[i]);
    return 0;
}