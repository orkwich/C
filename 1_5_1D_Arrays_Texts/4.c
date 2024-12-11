#include <stdio.h>

int main(void)
{
    printf("Podaj tekst: ");
    int count = 0;
    while(getchar() != '\n' && count < 1000)
        count++;
    printf("%d\n", count);
    return 0;
}