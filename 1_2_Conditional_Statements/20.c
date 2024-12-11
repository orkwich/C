#include <stdio.h>

int isxyz27(char znak)
{
    if(znak == 'x')
        return 1;
    if(znak == 'y')
        return 1;
    if(znak == 'z')
        return 1;
    if(znak == '2')
        return 1;
    if(znak == '7')
        return 1;
    return 0;
}

int main(void)
{
    printf("Podaj 5 znaków:");
    char znaki[6];
    scanf("%5s", znaki);
    int wystapienia = 0;
    wystapienia += isxyz27(znaki[0]);
    wystapienia += isxyz27(znaki[1]);
    wystapienia += isxyz27(znaki[2]);
    wystapienia += isxyz27(znaki[3]);
    wystapienia += isxyz27(znaki[4]);
    printf("Szukane znaki wystapily %d raz(y)", wystapienia);
    return 0;
}