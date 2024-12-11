#include <stdio.h>
#define EURO 4.2074
#define FUNT 4.7073
#define DOLAR 3.5382


int main(void)
{
    printf("Podaj pierwsza liczbe: ");
    float pln = 0;
    switch(scanf("%f", &pln))
    {
        case 1:
            break;
        default:
        {
            printf("incorrect input");
            return 1;
        }
    }

    switch(pln < 0)
    {
        case 1:
        {
            printf("incorrect input");
            return 1;
        }
    }

    printf("Podaj symbol operacji: ");
    char currency = '\0';
    getchar();
    scanf("%c", &currency);

    switch(currency)
    {
        case 'e':
        {
            float result = pln / EURO;
            printf("%0.2f", result);
            break;
        }
        case 'f':
        {
            float result = pln / FUNT;
            printf("%0.2f", result);
            break;
        }
        case 'd':
        {
            float result = pln / DOLAR;
            printf("%0.2f", result);
            break;
        }
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    return 0;
}