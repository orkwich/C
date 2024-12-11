#include <stdio.h>

int main(void)
{
    float numbers[10];
    printf("Podaj liczby:\n");
    for(int i = 0 ; i < 10; i+=2)
        if(scanf("%f %f", &numbers[i], &numbers[i+1]) != 2)
        {
            printf("Input data type error\n");
            return 1;
        }
    for(int i = 0; i < 10; i++)
        printf("%d %f\n", i, numbers[i]);
    return 0;
}