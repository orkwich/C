#include <stdio.h>

int main(void)
{
    printf("Podaj dwie liczby calkowite oddzielone spacja: ");
    int liczba1 = 0;
    int liczba2 = 0;
    if(scanf("%d %d", &liczba1, &liczba2) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("%d", liczba1 + liczba2);
    return 0;
}