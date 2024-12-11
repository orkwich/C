#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Podaj pierwsza przyprostokatna: ");
    double firstLength = 0;
    scanf("%lf", &firstLength);
    printf("Podaj druga przyprostokatna: ");
    double secondLength = 0;
    scanf("%lf", &secondLength);

    double thirdLength = sqrt(firstLength * firstLength + secondLength * secondLength);
    double sin1 = firstLength / thirdLength;
    double sin2 = secondLength / thirdLength;
    float ang1 = 0;
    float ang2 = 0;

    while(sin1 - sin(M_PI*(ang1/180)) > 0.00001 && ang1 < 90) ang1 += 0.01;
    while(sin2 - sin(M_PI*(ang2/180)) > 0.00001 && ang2 < 90) ang2 += 0.01;

    printf("Przeciwprostokatna: %.2lf\n%.2f\n%.2f", thirdLength, ang1, ang2);
    
    return 0;
}