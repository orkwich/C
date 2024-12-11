#include <stdio.h>

int main(void)
{
    printf("Podaj date: ");
    int day = 0;
    int month = 0;
    int year = 0;
    scanf("%2d-%2d-%4d", &day, &month, &year);
    printf("Day:%7c%02d\nMonth:%5c%02d\nYear:%4c%04d", ' ', day, ' ', month, ' ', year);
    return 0;
}