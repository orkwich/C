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
            printf("Dzien roboczy");
            break;
        }
        case 2:
        {
            printf("Dzien roboczy");
            break;
        }
        case 3:
        {
            printf("Dzien roboczy");
            break;
        }
        case 4:
        {
            printf("Dzien roboczy");
            break;
        }
        case 5:
        {
            printf("Dzien roboczy");
            break;
        }
        case 6:
        {
            printf("Weekend");
            break;
        }
        case 7:
        {
            printf("Weekend");
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