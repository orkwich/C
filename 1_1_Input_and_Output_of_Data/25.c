#include <stdio.h>

int main(void)
{
    printf("Podaj numer telefonu: ");
    int firstPart = 0;
    int secondPart = 0;
    int thirdPart = 0;
    scanf("%3d-%2d-%2d", &firstPart, &secondPart, &thirdPart);
    printf("Podaj numer kierunkowy: ");
    int prefix = 0;
    scanf("%2d", &prefix);
    printf("(%02d) %03d-%02d-%02d",prefix ,firstPart, secondPart, thirdPart);
    return 0;
}