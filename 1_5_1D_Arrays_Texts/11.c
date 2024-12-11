#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNumber(char character)
{
    if(character == '1')
        return 1;
    if(character == '2')
        return 1;
    if(character == '3')
        return 1;
    if(character == '4')
        return 1;
    if(character == '5')
        return 1;
    if(character == '6')
        return 1;
    if(character == '7')
        return 1;
    if(character == '8')
        return 1;
    if(character == '9')
        return 1;
    if(character == '0')
        return 1;
    
    return 0;
}

int check(char *string)
{
    int i = 0;
    while(string[i] != '\0')
    {
        if(!isNumber(string[i]) && string[i] != '|' && string[i] != '-')
            return 0;
        i++;
    }
    return 1;
}

int main(void)
{
    printf("Podaj wyrazenie:\n");
    char *string = malloc(sizeof(char) * 1000);
    scanf("%1000s", string);
    if(!check(string))
    {
        printf("Incorrect input");
        free(string);
        return 1;
    }

    long sums[1000];
    for(int i = 0; i < 1000; i++)
        sums[i] = 0;

    int i = 0;
    int j = 0;
    while(string[i] != '\0')
    {
        switch(string[i])
        {
            case '|':
            {
                i++;
                j++;
                break;
            }
            case '-':
            {
                i++;
                break;
            }
            default:
            {
                char *tmp = malloc(sizeof(char) * 100);
                int index = 0;
                while(isNumber(string[i]) && index < 99)
                    tmp[index++] = string[i++];
                tmp[++index] = '\0';
                sums[j] += atol(tmp);
                free(tmp);
            }
        }
    }
    for(i = 0; i <= j; i++)
        printf("%ld ", sums[i]);
    free(string);
    return 0;
}