#include <stdio.h>

int main(void)
{
    printf("Podaj temperature w stopniach Celsjusza: ");
    double celsjusz = 0;
    scanf("%lf", &celsjusz);
    printf("%.2lf\n%.2lf\n", celsjusz + 273.15, (double)celsjusz * 9 / 5 + 32);
    return 0;
}