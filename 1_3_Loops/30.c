#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    printf("Podaj n: ");
    int n = 0;
    if(scanf("%d", &n) != 1 || n > 10 || n <= 0)
    {
        printf("Improper input data");
        return 1;
    }
    float sum = 0;
    for(int i = 0; i < n; i++)
    {
        float randomFloat = (float) rand() / RAND_MAX;
        randomFloat *= 10;
        randomFloat -= 5;
        sum += randomFloat;
        printf("%.6f\n", randomFloat);
    }
    printf("%.4f\n", sum);
    return 0;
}