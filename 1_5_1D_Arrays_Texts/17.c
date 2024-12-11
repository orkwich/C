#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int isLetter(char character)
{
    if(character >= 'a' && character <= 'z')
        return 1;
    if(character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

int isVowel(char character)
{
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

int countWords(char tab[])
{
    if(*tab == '\0')
        return 0;
    int i = 0;
    int result = 0;
    while(tab[i] != '\0')
        if(tab[i++] == ' ')
            result++;
    return ++result;
}

int wordLen(char tab[])
{
    int i = 0;
    while(*tab != ' ' && *tab++ != '\0')
        i++;
    return i;
}

char** separateWords(char tab[])
{
    int words = countWords(tab);
    char **result = malloc(sizeof(char*) * words);
    int i = 0;
    int j = 0;
    result[i] = malloc(sizeof(char) * wordLen(tab));
    while(*tab != '\0')
        if(*tab != ' ')
            result[i][j++] = *tab++;
        else
        {
            result[i][j] = '\0';
            result[++i] = malloc(sizeof(char) * wordLen(tab++));
            j = 0;
        }
    result[i][j] = '\0';
    return result;
}

int main(void)
{
    printf("Podaje tekst:\n");
    char *string = malloc(sizeof(char) * (SIZE + 1));
    int i = 0;
    while(scanf("%c", &string[i]) && string[i] != '\n' && i++ <= (SIZE + 1));
    string[i] = '\0';
    i = 0;
    while(string[i] != '\0')
    {
        if(!isLetter(string[i]) && string[i] != ' ')
        {
            printf("Incorrect input");
            return 1;
        }
        i++;
    }

    int countSpaces = 0;
    int countVowels = 0;
    int countConsonants = 0;
    float ratios[SIZE];

    for(i = 0; i < SIZE; i++)
        ratios[i] = 0;

    i = 0;
    while(string[i] != '\0')
    {

        if(isVowel(string[i]))
            countVowels++;
        else if(string[i] != ' ')
            countConsonants++;
        else
        {
            ratios[countSpaces++] = (float) countVowels / (float) countConsonants;
            countVowels = 0;
            countConsonants = 0;
        }
        i++;
    }
    ratios[countSpaces] = (float) countVowels / (float) countConsonants;

    int *maxIndexes = malloc(sizeof(int) * (countSpaces + 1));
    int maxIndexWrittenCount = 0;
    float max = 0;
    for(i = 0; i <= countSpaces; i++)
        maxIndexes[i] = -1;
    i = 0;
    while(i <= countSpaces)
    {
        if(max == ratios[i])
            maxIndexes[maxIndexWrittenCount++] = i;
        if(max < ratios[i])
        {
            max = ratios[i];
            maxIndexWrittenCount = 0;
            maxIndexes[maxIndexWrittenCount++] = i;
        }
        i++;
    }
    char **separated = separateWords(string);
    for(i = maxIndexWrittenCount - 1; i >= 0; i--)
        printf("%s\n", separated[maxIndexes[i]]);
    return 0;
}