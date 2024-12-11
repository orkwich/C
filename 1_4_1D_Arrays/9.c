#include <stdio.h>

int main(void)
{
    printf("Podaja dane:\n");
    int numbers[100];
    int index = 0;
    int max = -__INT32_MAX__;
    int min = __INT32_MAX__;
    int sum = 0;
    do
    {
        if(scanf("%d", &numbers[index]) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if(numbers[index] == -1)
            break;
        if(numbers[index] > max)
            max = numbers[index];
        if(numbers[index] < min)
            min = numbers[index];
        sum += numbers[index];
    } while(numbers[index++] != -1 && index < 100);

    float avg = (float) sum / (float) index;
    printf("%d\n%d\n%d\n%f\n%d\n", index, min, max, avg, sum);
    
    return 0;
}