#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Program rozwiazujacy rownanie kwadratowe postaci 0 = ax^2 + bx + c \nPodaj a: ");
    float a = 0;
    scanf("%f", &a);
    float b = 0;
    printf("Podaj b: ");
    scanf("%f", &b);
    float c = 0;
    printf("Podaj c: ");
    scanf("%f", &c);

    if(a == 0 && b != 0)
    printf("jeden pierwiastek %f", -c / b);
        
    if((a == 0 && b == 0 && c != 0) || (a != 0 && (b * b) - (4 * c * a) < 0))
        printf("brak");

    if(a == 0 && b == 0 && c == 0)
        printf("nieskonczonosc");

    if(a != 0 && (b * b) - (4 * c * a) == 0)
        printf("jeden pierwiastek %f", (-b) / (2 * a));

    if(a != 0 && (b * b) - (4 * c * a) > 0)
        printf("dwa pierwiastki: %f %f", (-b - sqrt((b * b) - (4 * c * a))) / (2 * a), (-b + sqrt((b * b) - (4 * c * a))) / (2 * a));

    return 0;
}