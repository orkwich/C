#include <stdio.h>

int main(void)
{
    printf("podaj liczby:\n");
    int input = 0;
    int sumEven = 0;
    int sumOdd = 0;
    while(input != -1)
    {
        if(scanf("%d", &input) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if(input % 2 == 0)
            sumEven += input;
        else if(input != -1)
            sumOdd += input;
    }
    printf("Suma liczb parzystych: %d\nSuma liczb nieparzystych: %d\n", sumEven, sumOdd);
    return 0;
}