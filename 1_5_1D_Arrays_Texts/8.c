#include <stdio.h>
#include <stdlib.h>

int isLetter(char character)
{
    if(character >= 'a' && character <= 'z')
        return 1;
    if(character >= 'A' && character <= 'Z')
        return 1;
    return 0;
}

int isNumber(char character)
{
    if(character >= '1' && character <= '9')
        return 1;
    return 0;
}

int main(void)
{
    printf("Podaj tekst: ");
    int i = 0;
    char string[100];
    char tmp = '\0';
    while((tmp = getchar()) != '\n')
    {
        if(!isLetter(tmp) && !isNumber(tmp))
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
    if(isNumber(string[i - 1]))
    {
        printf("Incorrect input");
        return 1;
    }
    for(int j = 1; j < i; j++)
    {
        if(isNumber(string[j - 1]) && isNumber(string[j]))
        {
            printf("Incorrect input");
            return 1;
        }
    }
    char output[201];
    int outputLength = 0;
    i--;
    for(int j = 0; j <= i; j++)
        if(isLetter(string[i - j]))
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
            char number[1] = {string[i - j]};
            for(int ii = 0; ii < atoi(number) - 1; ii++)
            {
                output[outputLength++] = string[i - j + 1];
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