#include <stdio.h>

int main(void)
{
    printf("Podaj miesiac: ");
    int month = 0;
    switch(scanf("%d", &month))
    {
        case 1:
            break;
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    switch(month < 1 || month > 12)
    {
        case 1:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    switch(month)
    {
        case 1:
        {
            printf("Styczen");
            break;
        }
        case 2:
        {
            printf("Luty");
            break;
        }
        case 3:
        {
            printf("Marzec");
            break;
        }
        case 4:
        {
            printf("Kwiecien");
            break;
        }
        case 5:
        {
            printf("Maj");
            break;
        }
        case 6:
        {
            printf("Czerwiec");
            break;
        }
        case 7:
        {
            printf("Lipiec");
            break;
        }
        case 8:
        {
            printf("Sierpien");
            break;
        }
        case 9:
        {
            printf("Wrzesien");
            break;
        }
        case 10:
        {
            printf("Pazdziernik");
            break;
        }
        case 11:
        {
            printf("Listopad");
            break;
        }
        case 12:
        {
            printf("Grudzien");
            break;
        }
    }
    return 0;
}