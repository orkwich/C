#include <stdio.h>

int main(void)
{
    int numbers[10];
    printf("Podaj liczby: ");
    for(int i = 0; i < 10; i+=2)
    {
        if(scanf("%d %d", &numbers[i], &numbers[i+1]) != 2)
        {
            printf("Input data type error\n");
            return 1;
        }
    }

    int max = numbers[0];
    int min = numbers[0];
    int sum = 0;
    for(int i = 0; i < 10; i++)
    {
        if(max < numbers[i])
            max = numbers[i];
        if(min > numbers[i])
            min = numbers[i];
        sum += numbers[i];
    }

    float average = (float) sum / 10;
    printf("%.4f\n%d\n%d\n", average, max, min);

    return 0;
}