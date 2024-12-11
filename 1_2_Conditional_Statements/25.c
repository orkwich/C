#include <stdio.h>

int main(void)
{
    printf("Podaj x: ");
    int number = 0;
    switch(scanf("%d", &number))
    {
        case 1:
        {
            int isPositive = number > 0;
            int isNegative = number < 0;
            char *answers[3] = {"is equal to 0\0", "is positive\0", "is negative\0"};

            printf("%d %s", number,  answers[0 + isPositive * 1 + isNegative * 2]);
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