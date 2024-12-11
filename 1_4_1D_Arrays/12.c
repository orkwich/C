#include <stdio.h>

int main(void)
{
    printf("podaj liczby:\n");
    int numbers[1000];
    int sum = 0;
    int index = 0;
    do
    {
        if(scanf("%d", &numbers[index]) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if(!numbers[index] && index == 0)
        {
            printf("Brak danych");
            return 0;
        }
        sum += numbers[index];
    } while(numbers[index++] != 0 && index < 1000);

    int sumGreater = 0;
    int sumLower = 0;
    float avg = (float) sum / (float) (index - 1);
    for(int i = 0; i < index; i++)
    {
        if(numbers[i] < avg)
            sumLower += numbers[i];
        if(numbers[i] > avg)
            sumGreater += numbers[i];
    }
    printf("%.2f\n%d\n%d\n", avg, sumGreater, sumLower);
    return 0;
}