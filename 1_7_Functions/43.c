#include <stdio.h>

void adjust(char *tab, int places)
{
    if(*tab == '\0')
        return;
    if(places < 0)
    {
        int i = 0;
        do
            tab[i] = tab[i - places];
        while(tab[i++ - places] != '\0');
    }
    if(places > 0)
    {
        char *tmpTab = tab;
        while(*tmpTab)
            tmpTab++;
        while(tmpTab != tab)
        {
            *(tmpTab + places) = *tmpTab;
            tmpTab--;
        }
    }
}

void replace(char tab[], char from, char to)
{
    while(*tab)
    {
        if(*tab == from)
            *tab = to;
        tab++;
    }
}

void replace_string(char tab[], const char from[], const char to[])
{
    int k = 0;
    while(to[k] != '\0')
        if(from[k++] == '\0')
            return;
    while(*tab)
    {
        int i = 0;
        if(*from == *tab)
        {
            while(from[i] == tab[i])
            {
                i++;
                if(from[i] == '\0')
                {
                    int j = 0;
                    while(to[j] != '\0')
                    {
                        tab[j] = to[j];
                        j++;
                    }
                    adjust(tab + j, j - i);
                }
            }
        }
        tab++;
    }
}

int isVowel(char character)
{
    switch(character)
    {
        case 'a':
        {
            return 1;
        }
        case 'o':
        {
            return 1;
        }
        case 'e':
        {
            return 1;
        }
        case 'u':
        {
            return 1;
        }
        case 'i':
        {
            return 1;
        }
        case 'y':
        {
            return 1;
        }
        case 'A':
        {
            return 1;
        }
        case 'O':
        {
            return 1;
        }
        case 'E':
        {
            return 1;
        }
        case 'U':
        {
            return 1;
        }
        case 'I':
        {
            return 1;
        }
        case 'Y':
        {
            return 1;
        }
    }
    return 0;
}

void replaceThe(char *string)
{
    replace_string(string, "the", " ");
    replace_string(string, "The", " ");
    replace_string(string, "tHe", " ");
    replace_string(string, "thE", " ");
    replace_string(string, "THe", " ");
    replace_string(string, "tHE", " ");
    replace_string(string, "ThE", " ");
    replace_string(string, "THE", " ");
}

int main(void)
{
    printf("Podaj tekst:\n");
    char string[1001];
    int i = 0;
    while((string[i++] = getchar()) != '\n' && i <= 1000);
    string[i - 1] = '\0';
    char stringCopy[1001];
    i = 0;
    do
    {
        stringCopy[i] = string[i];
    } while(string[i++] != '\0');
    i = 0;
    while(string[i] != '\0')
    {
        if(isVowel(string[i]))
            string[i]++;
        i++;
    }
    replaceThe(stringCopy);
    printf("%s\n", string);
    printf("%s\n", stringCopy);
    return 0;
}