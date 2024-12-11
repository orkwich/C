#include <stdio.h>

int main(void)
{
    printf("Podaj dziesiec liczb:\n");
    int liczby[10] = {0,0,0,0,0,0,0,0,0,0};
    scanf("%d %d %d %d %d %d %d %d %d %d", &liczby[0], &liczby[1], &liczby[2], &liczby[3], &liczby[4], &liczby[5], &liczby[6], &liczby[7], &liczby[8], &liczby[9]);
    printf("Srednia artmetyczna= %.4lf", (double)(liczby[0] + liczby[1] + liczby[2] + liczby[3] + liczby[4] + liczby[5] + liczby[6] + liczby[7] + liczby[8] + liczby[9])/10);
    return 0;
}