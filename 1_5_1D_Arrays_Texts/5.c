#include <stdio.h>

int isNewVowel(char character, char *vowelsUsed)
{
    while(*vowelsUsed != '\0')
    {
        if(character == *vowelsUsed)
            return 0;
        vowelsUsed++;
    }

    switch(character)
    {
        case 'A':
        {
            return 1;
        }
        case 'E':
        {
            return 1;
        }
        case 'I':
        {
            return 1;
        }
        case 'O':
        {
            return 1;
        }
        case 'U':
        {
            return 1;
        }
        case 'Y':
        {
            return 1;
        }
        case 'a':
        {
            return 1;
        }
        case 'e':
        {
            return 1;
        }
        case 'i':
        {
            return 1;
        }
        case 'o':
        {
            return 1;
        }
        case 'u':
        {
            return 1;
        }
        case 'y':
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    printf("Podaj tekst:\n");
    int i = 0;
    int count = 0;
    char tmp = '\0';
    char vowels[13];
    for(int j = 0; j < 13; j++)
        vowels[j] = '\0';
    
    while((tmp = getchar()) != '\n' && i++ < 1000)
        if(isNewVowel(tmp, vowels))
            vowels[count++] = tmp;

    printf("%d", count);
    return 0;
}