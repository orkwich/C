#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Podaj liczbe calkowita: ");
    int number = 0;
    switch(scanf("%d", &number))
    {
        case 1:
            break;
        default:
        {
            printf("Incorrect input\n");
            return 1;
        }
    }

    char *output[2] = {"even", "odd"};
    int tmp = -number * (number < 0) + number * (number >= 0);
    printf("%d is %s\n", number, output[tmp % 2]);
    return 0;
}