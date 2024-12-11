#include <stdio.h>
#include <stdlib.h>

int isLowercase(char character)
{
    if(character >= 'a' && character <= 'z')
        return 1;
    return 0;
}

int isUpperCase(char character)
{
    if(character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

int isLetter(char character)
{
    return isLowercase(character) || isUpperCase(character);
}

int main(void)
{
    printf("Podaj tekst: ");
    int i = 0;
    char string[100];
    char tmp = '\0';
    while((tmp = getchar()) != '\n')
    {
        if(!isLetter(tmp) && tmp != ' ')
        {
            printf("Incorrect input");
            return 1;
        }
        if(i == 100)
        {
            printf("Input is too long");
            return 2;
        }
        string[i++] = tmp;
    }
    char output[201];
    int outputLength = 0;
    i--;
    for(int j = 0; j <= i; j++)
        if(isLowercase(string[i - j]) || string[i - j] == ' ')
        {
            output[outputLength++] = string[i - j];
            if(outputLength > 200)
            {
                printf("Output is too long");
                return 3;
            }
        }
        else
        {
            for(int ii = 0; ii < 3; ii++)
            {
                output[outputLength++] = string[i - j];
                if(outputLength > 200)
                {
                    printf("Output is too long");
                    return 3;
                }
            }
        }
    output[outputLength] = '\0';
    printf("%s", output);
    return 0;
}