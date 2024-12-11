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

    if(a == 0)
        if(b == 0)
            if(c == 0)
                printf("nieskonczonosc");
            else
                printf("brak");
        else
            printf("jeden pierwiastek %f", -c / b);
    else
    {
        if((b * b) - (4 * c * a) == 0)
            printf("jeden pierwiastek %f", (-b) / (2 * a));
        else if((b * b) - (4 * c * a) < 0)
            printf("brak");
        else
        {
            b = -b;
            printf("dwa pierwiastki: %f %f", (-b - sqrt((b * b) - (4 * c * a))) / (2 * a), (-b + sqrt((b * b) - (4 * c * a))) / (2 * a));
        }
    }

    return 0;
}