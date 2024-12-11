#include <stdio.h>

int isChessLetter(char character)
{
    if(character >= 'a' && character <='h') return 1;
    if(character >= 'A' && character <='H') return 1;
    return 0;
}

int main(void)
{
    printf("Podaj pole: ");
    char letter = '\0';
    int number = 0;
    if(scanf("%c%d", &letter, &number) != 2 || !isChessLetter(letter) || number < 1 || number > 8)
    {
        printf("Incorrect input");
        return 1;
    }
    if((number + letter) % 2 == 1)
        printf("white");
    else
        printf("black");
    return 0;
}