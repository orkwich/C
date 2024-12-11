#include <stdio.h>
#define SIZE 1000

int isLetter(char character)
{
    if(character >= 'a' && character <= 'z')
        return 1;
    if(character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

int countWords(char tab[])
{
    if(*tab == '\0')
        return 0;
    int i = 0;
    int result = 0;
    do
    {
        while(!isLetter(tab[i]) && tab[i] != '\0')
            i++;
        if(isLetter(tab[i]))
        {
            result++;
            while(isLetter(tab[i]) && tab[i] != '\0')
                i++;
        }
    } while(tab[i] != '\0');
    
    return result;
}

int main(void)
{
    printf("podaj tekst: ");
    char string[SIZE + 1];
    int i = 0;
    while((string[i] = getchar()) != '\n' && i < SIZE)
        i++;
    string[i] = '\0';
    printf("%s\n%d", string, countWords(string));
    return 0;
}