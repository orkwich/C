#include <stdio.h>

int main(void)
{
    printf("Podaj pierwsza liczbe calkowita: ");
    int liczba1 = 0;
    if(scanf("%d", &liczba1) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj druga liczbe calkowita: ");
    int liczba2 = 0;
    if(scanf("%d", &liczba2) != 1)
    {
        printf("Incorrect input");
        return 1;
    }

    if(!liczba2)
    {
        printf("Operation not permitted");
        return 1;
    }

    if(liczba1 % liczba2 == 0)
        printf("%d is divisible by %d", liczba1, liczba2);
    else    
        printf("%d is not divisible by %d", liczba1, liczba2);
    return 0;
}