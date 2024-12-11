#include <stdio.h>
#include <stdlib.h>

void wiatraczki(int n)
{
    int tmp = n;
    if(n < 0)
        n = -n;
    n *= 2;
    char **wiatraczek = malloc(sizeof(char*) * n);
    for(int i = 0; i < n; i++)
        *(wiatraczek + i) = malloc(sizeof(char) * n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            *(*(wiatraczek + i) + j) = ' ';
    for(int i = 0; i < 2; i++)
    {
        *((*(wiatraczek + ((n / 2) - i))) + (n / 2)) = 'X';
        *((*(wiatraczek + ((n / 2) - i))) + ((n / 2) - 1)) = 'X';
    }
    for(int i = 0; i < n; i++)
    {
        if(tmp > 0 && i < (n / 2))
        {
            for(int j = 0; j <= i; j++)
                *((*(wiatraczek + i)) + j) = 'X';
            for(int j = (n / 2); j <= (n - 1 - i); j++)
                *((*(wiatraczek + i)) + j) = 'X';
        }
        if(tmp < 0 && i < (n / 2))
        {
            for(int j = n - 1 - i; j < n; j++)
                *((*(wiatraczek + i)) + j) = 'X';
            for(int j = i; j < (n / 2); j++)
                *((*(wiatraczek + i)) + j) = 'X';
        }
        if(tmp > 0 && i >= (n / 2))
        {
            for(int j = n - 1 - i; j < (n / 2); j++)
                *((*(wiatraczek + i)) + j) = 'X';
            for(int j = i; j < n; j++)
                *((*(wiatraczek + i)) + j) = 'X';
        }
        if(tmp < 0 && i >= (n / 2))
        {
            for(int j = 0; j <= n - 1 - i; j++)
                *((*(wiatraczek + i)) + j) = 'X';
            for(int j = n / 2; j <= i; j++)
                *((*(wiatraczek + i)) + j) = 'X';
        }
        //for(int i = 0; i < n; i++)
        //    free(*(wiatraczek + i));
        //free(wiatraczek);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%c", *(*(wiatraczek + i) + j));
        printf("\n");
    }
}

int main(void)
{
    int liczby[11];
    int i = 0;
    int liczba = 1;
    while(liczba && i < 11)
    {
        printf("Podaj liczbe: ");
        scanf("%d", &liczba);
        if(liczba > 10 || liczba < -10 || liczba == 0)
            break;
        liczby[i++] = liczba;
    }
    for(int j = 0; j < i; j++)
        wiatraczki(liczby[j]);
    return 0;
}