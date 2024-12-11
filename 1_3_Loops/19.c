#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe calkowita: ");
    double input = 0;
    if(scanf("%lf", &input) != 1 || input - (int)input != 0)
    {
        printf("Incorrect input");
        return 1;
    }

    int number = input;
    int i = 2;
    int dividerCout = 0;
    if(number < 2) dividerCout++;
    while(dividerCout == 0 && i <= number/i)
        if(!(number % i++)) dividerCout++;
    
    if(dividerCout > 0)
        printf("NO");
    else printf("YES");

    return 0;
}