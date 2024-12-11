#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int number = rand() % 101;
    int input;
    int i=0;
    while(i < 10)
    {
        printf("Zgadnij: ");
        scanf("%d", &input);
        if(input < number) printf("za malo\n");
        else if(input > number) printf("za duzo\n");
        else break;
        i++;
    }
    if(i < 9) printf("wygrales");
    else printf("przegrales");
    return 0;
}