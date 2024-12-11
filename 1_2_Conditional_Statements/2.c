#include <stdio.h>

int main(void)
{
    printf("Podaj numer telefonu: ");
    int kierunkowy = 0;
    //cyfry numeru
    int pierwszeTrzy = 0;
    int kolejneDwie = 0;
    int ostatnieDwie = 0;
    if(scanf("(%2d) %3d-%2d-%2d", &kierunkowy, &pierwszeTrzy, &kolejneDwie, &ostatnieDwie) != 4 || kierunkowy < 0 || pierwszeTrzy < 0 || kolejneDwie < 0 || ostatnieDwie < 0)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Numer kierunkowy: %02d\nNumer telefonu: %03d-%02d-%02d", kierunkowy, pierwszeTrzy, kolejneDwie, ostatnieDwie);
    return 0;
}