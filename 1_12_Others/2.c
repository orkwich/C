#include <stdio.h>
#include <stdlib.h>

int my_pow(int x, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return x;
    return my_pow(x, n - 1) * x;
}

void cantor(int n)
{
    int len = my_pow(3, n - 1);
    char *output = malloc(sizeof(char) * (len + 1));
    for(int i = 0; i < len; i++)
        *(output + i) = '_';
    *(output + len) = '\0';
    int k = len / 3;
    for(int i = 0; i < n; i++)
    {
        printf("%s\n", output);
        if(k != 0)
            for(int j = 0; j < len; j++)
                if((j / k) % 2)
                    *(output + j) = ' ';
        k /= 3;
    }
    free(output);
}

int main(void)
{
    printf("Podaj glebokosc: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n < 1 || n > 6)
    {
        printf("Incorrect input data");
        return 2;
    }
    cantor(n);
    return 0;
}