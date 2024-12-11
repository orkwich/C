#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Podaj wartosc a: ");
    int wartoscA = 0;
    scanf("%d", &wartoscA);

    printf("Podaj wartosc b: ");
    int wartoscB = 0;
    scanf("%d", &wartoscB);

    printf("Podaj wartosc c: ");
    int wartoscC = 0;
    scanf("%d", &wartoscC);

    printf("%.2lf", sqrt((double) (wartoscA * wartoscA + wartoscB * wartoscB + wartoscC * wartoscC)));

    return 0;
}