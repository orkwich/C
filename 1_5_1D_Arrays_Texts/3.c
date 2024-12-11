#include <stdio.h>

int main(void)
{
    printf("Podaj imie: ");
    char name[31];
    scanf("%30s", name);
    printf("Witaj %s!", name);
    return 0;
}