#include <stdio.h>

int main(void)
{
    printf("podaj 5 liczb:\n");
    double numbers[5] = {0,0,0,0,0};
    scanf("%lf %lf %lf %lf %lf", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]);

    double max = numbers[0];
    double min = numbers[0];

    if(max < numbers[1])
        max = numbers[1];
    if(min > numbers[1]) 
        min = numbers[1];

    if(max < numbers[2])
        max = numbers[2];
    if(min > numbers[2])
        min = numbers[2];

    if(max < numbers[3])
        max = numbers[3];
    if(min > numbers[3])
        min = numbers[3];

    if(max < numbers[4])
        max = numbers[4];
    if(min > numbers[4])
        min = numbers[4];

    double average = (numbers[0] + numbers[1] + numbers[2] + numbers[3] + numbers[4]) / 5;

    printf("%lf\n%lf\n%.2lf\n", min, max, average);

    return 0;
}