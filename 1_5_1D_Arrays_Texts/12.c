#include <stdio.h>
#include <stdlib.h>

int isNumber(char character)
{
    if(character >= '0' && character <= '9')
        return 1;
    return 0;
}

void clearChar(char string[], int strlen)
{
    for(int i = 0; i < strlen; i++)
        string[i] = '\0';
}

int main(void)
{
    printf("Podaj tekst:\n");
    char string[101];
    int i = 0;
    while((string[i] = getchar()) != '\n' && i < 100)
    {
        if(!isNumber(string[i]) && string[i] != '-' && string[i] != '+')
        {
            printf("Incorrect input");
            return 1;
        }
        i++;
    }
    string[i] = '\0';
    char currentNumber[101];
    clearChar(currentNumber, 101);
    int curNumIterator = 0;
    i = 0;
    int result = 0;
    while(string[i] != '\0')
    {
        if(!isNumber(string[i]))
        {
            result += atoi(currentNumber);
            clearChar(currentNumber, curNumIterator);
            curNumIterator = 0;
        }
        currentNumber[curNumIterator++] = string[i++];
    }
    result += atoi(currentNumber);
    printf("%d", result);
    return 0;
}