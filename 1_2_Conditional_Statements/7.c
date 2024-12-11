#include <stdio.h>

int main(void)
{
    printf("Podaj ilosc kWh: ");
    int kWh = 0;
    if(scanf("%d", &kWh) != 1 || kWh < 0)
    {
        printf("Incorrect input");
        return 1;
    }

    float result = 0;
    float vat = 1.22;
    if(kWh > 250)
    {
        result += (float)(kWh - 250) * 1.5;
        kWh = 250;
    }
    if(kWh > 150)
    {
        result += (float)(kWh - 150) * 1.2;
        kWh = 150;
    }
    if(kWh > 50)
    {
        result += (float)(kWh - 50) * 0.75;
        kWh = 50;
    }
    result += (float)kWh * 0.5;
    result *= vat;
    printf("Koszt brutto: %lf", result);
    return 0;
}