#include <stdio.h>

int even_odd(int s, int n)
{
    if(n < 0)
        return 0;
    if(n == 0)
        return s;
    int tmp = even_odd(s, n - 1);
    if(tmp % 2)
        return (tmp * 3) + 1;
    else
        return tmp / 2;
    return 0;
}

int main(void)
{
    printf("Podaj wartosc pierwszego wyrazu: ");
    int s = 0;
    if(scanf("%d", &s) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj numer wyrazu, ktorego wartosc chcesz wyznaczyc: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n < 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %d\n", even_odd(s, n));
    return 0;
}