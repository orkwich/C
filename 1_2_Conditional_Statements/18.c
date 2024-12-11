#include <stdio.h>

int main()
{
    printf("prosze podac liczbe punktow: ");
    int liczbaPkt = 0;
    if(scanf("%d", &liczbaPkt) != 1 || liczbaPkt > 20 || liczbaPkt < 0)
    {
        printf("Incorrect input");
        return 1;
    }

    int ocena = 0;
    if(liczbaPkt <= 10)
        ocena = 2;
    if(liczbaPkt > 10 && liczbaPkt <= 13)
        ocena = 3;
    if(liczbaPkt > 13 && liczbaPkt <= 16)
        ocena = 4;
    if(liczbaPkt > 16 && liczbaPkt <= 20)
        ocena = 5;
    printf("ocena: %d", ocena);
    return 0;
}