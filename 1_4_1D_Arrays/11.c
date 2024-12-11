#include <stdio.h>

int main(void)
{
    printf("podaj liczby: ");
    int akumulator[11];
    for(int i = 0; i < 11; i++)
        akumulator[i] = 0;
    
    int tmp = 0;
    do
    {
        if(scanf("%d", &tmp) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if(tmp >= 0 && tmp <= 10)
            akumulator[tmp]++;
    } while(tmp != -1);

    for(int i = 0; i < 11; i++)
        printf("%d - %d\n", i, akumulator[i]);
    
    return 0;
}