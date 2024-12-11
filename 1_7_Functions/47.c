#include <stdio.h>
#include <math.h>

int my_itoa(int a, char tab[], int size)
{
    if(size <= 0)
        return 1;
    if(a < 0)
    {
        *tab++ = '-';
        a *= -1;
        if(--size == 0)
            return 1;
    }
    char *tmpTab = tab;
    int j = 0;
    do
    {
        *tmpTab++ = '0' + (a % 10);
        a /= 10;
        j++;
        if(--size == 0)
            return 1;
    } while(a > 0);
    *tmpTab = '\0';
    j--;
    for(int i = 0; i < j; i++, j--)
    {
        char tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
    return 0;
}
int my_ftoa(float a, int precision, char tab[], int size)
{
    if(size <= precision + 2)
        return 1;
    if(my_itoa(a, tab, size))
        return 1;
    if(a < 0)
        a *= -1;
    while(*tab != '\0')
    {
        tab++;
        if(--size == 0)
            return 1;
    }
    //if(a == 0)
    //{
    //    *tab = '\0';
    //    return 0;
    //}
    *tab++ = '.';
    if(--size == 0)
        return 1;
    a -= (int)a;
    while(precision--)
    {
        a *= 10;
        *tab++ = '0' + ((int)a % 10);
        if(--size == 0)
            return 1;
    }
    a *= 10;
    *++tab = '\0';
    return 0;
}

int main(void)
{
    printf("podaj liczbe: ");
    float number = 0;
    if(!scanf("%f", &number))
    {
        printf("Incorrect input");
        return 1;
    }
    char myInt[100];
    char myFloat[100];
    for(int i = 0; i < 100; i++)
    {
        myInt[i] = '\0';
        myFloat[i] = '\0';
    }
    my_itoa((int)number, myInt, 100);
    my_ftoa(number, 4, myFloat, 100);
    printf("%s\n%s\n", myInt, myFloat);
    return 0;
}