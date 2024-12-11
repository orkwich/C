#include <stdio.h>

int main(void)
{
    printf("Podaj dzien tygodnia: ");
    int day = 0;
    scanf("%d", &day);
    switch(day)
    {
        case 1:
        {
            printf("poniedzialek");
            break;
        }
        case 2:
        {
            printf("wtorek");
            break;
        }
        case 3:
        {
            printf("sroda");
            break;
        }
        case 4:
        {
            printf("czwartek");
            break;
        }
        case 5:
        {
            printf("piatek");
            break;
        }
        case 6:
        {
            printf("sobota");
            break;
        }
        case 7:
        {
            printf("niedziela");
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