#include <stdio.h>

int main(void)
{
    printf("podaj 5 liczb:\n");
    double numbers[5] = {-1,-1,-1,-1,-1};
    int numbersReadCout = 0;

    scanf("%lf", &numbers[0]);
    if(numbers[0] != -1)
    {
        scanf(" %lf", &numbers[1]);
        numbersReadCout++;
    }
    if(numbers[1] != -1)
    {
        scanf(" %lf", &numbers[2]);
        numbersReadCout++;
    }
    if(numbers[2] != -1)
    {
        scanf(" %lf", &numbers[3]);
        numbersReadCout++;
    }
    if(numbers[3] != -1)
    {
        scanf(" %lf", &numbers[4]);
        numbersReadCout++;
    }
    if(numbers[4] != -1) numbersReadCout++;

    double max = numbers[0];
    double min = numbers[0];
    double sum = numbers[0];

    if(numbersReadCout > 1)
    {
        if(max < numbers[1]) max = numbers[1];
        if(min > numbers[1]) min = numbers[1];
        sum += numbers[1];
    }

    if(numbersReadCout > 2)
    {
        if(max < numbers[2]) max = numbers[2];
        if(min > numbers[2]) min = numbers[2];
        sum += numbers[2];
    }

    if(numbersReadCout > 3)
    {
        if(max < numbers[3]) max = numbers[3];
        if(min > numbers[3]) min = numbers[3];
        sum += numbers[3];
    }

    if(numbersReadCout > 4)
    {
        if(max < numbers[4]) max = numbers[4];
        if(min > numbers[4]) min = numbers[4];
        sum += numbers[4];
    }

    double average = 0;
    if(numbersReadCout)
    {
        average = sum / numbersReadCout;
        printf("%lf\n%lf\n%.2lf\n", min, max, average);
    }

    return 0;
}