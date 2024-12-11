#include <stdio.h>

int swap(int *a, int *b)
{
    if(a == NULL || b == NULL)
        return 1;
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}

int main(void)
{
    printf("Wpisz 2 liczby int oddzielajac spacja\n");
    int a = 0;
    int b = 0;
    if(scanf("%d %d", &a, &b) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    swap(&a, &b);
    printf("a: %d, b: %d", a, b);
    return 0;
}