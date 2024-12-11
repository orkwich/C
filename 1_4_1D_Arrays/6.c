#include <stdio.h>

int main(void)
{
    int numbers[10];
    printf("Podaj liczby:\n");
    for(int i = 0 ; i < 10; i+=2)
        if(scanf("%d %d", &numbers[i], &numbers[i+1]) != 2)
        {
            printf("Input data type error\n");
            return 1;
        }
    for(int i = 0; i < 10; i++)
    {
        printf("%d ", numbers[i]);
        if(numbers[i] % 2 == 0)
            printf("even\n");
        else
            printf("odd\n");

    }

    return 0;
}