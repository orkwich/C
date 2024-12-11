#include <stdio.h>

int main(void)
{
    char tekst[] = {'T','o',' ','j','e','s','t',' ','t','e','k','s','t','\x0'};
    int i = 0;
    while(tekst[i] != '\x0')
    {
        putc(tekst[i], stdout);
        printf(" %d %c\n", tekst[i], tekst[i]);
        i++;
    }

    return 0;
}