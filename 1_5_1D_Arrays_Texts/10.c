#include <stdio.h>
#include <string.h>

int isLetter(char character)
{
    if(character >= 'a' && character <= 'z')
        return 1;
    if(character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

int checkInput(char *string)
{
    while(*string != '\0')
    {
        if(!isLetter(*string) && *string != ' ')
            return 0;
        string++;
    }
    return 1;
}

int main(void)
{
    printf("Podaje tekst:\n");
    char words[1000];
    int tmp = 0;
    int countWords = 0;
    while((tmp = getchar()) != '\n' && countWords < 1000)
        words[countWords++] = tmp;
    words[countWords] = '\0';

    if(!checkInput(words))
    {
        printf("Incorrect input");
        return 1;
    }
    
    int maxWordLength = 0;
    int tmpWordLength = 0;
    int maxIndexes[1000];
    int indexCount = 0;
    for(int i = 0; i < 1000; i++)
        maxIndexes[i] = -1;

    for(int i = 0; i <= countWords; i++)
    {
        if(words[i] == ' ' || words[i] == '\0')
        {
            if(tmpWordLength > maxWordLength)
            {
                maxWordLength = tmpWordLength;
                indexCount = 0;
            }
            if(tmpWordLength == maxWordLength)
                maxIndexes[indexCount++] = i - maxWordLength;
            tmpWordLength = 0;
        }
        else
            tmpWordLength++;
    }

    printf("%d %d\n", indexCount, maxWordLength);
    for(int i = indexCount - 1; i >= 0; i--)
    {
        for(int j = maxIndexes[i]; j < maxWordLength + maxIndexes[i]; j++)
            printf("%c", words[j]);
        printf("\n");
    }
    return 0;
}