#include <stdio.h>

int main(void)
{
    printf("Wprowadz 5 liczb:\n");
    float liczby[5] = {0,0,0,0,0};
    scanf("%f %f %f %f %f", &liczby[0], &liczby[1], &liczby[2], &liczby[3], &liczby[4]);
    printf("Srednia artmetyczna= %.4lf", (double)(liczby[0] + liczby[1] + liczby[2] + liczby[3] + liczby[4])/5);
    return 0;
}