#include <stdio.h>
#define SIZE 1000

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int my_strlen(char* str)
{
    int i = 0;
    while(*(str + i) != '\0')
        i++;
    return i;
}

char* reverse(char* text)
{
    if(text == NULL)
        return NULL;
    int text_len = my_strlen(text);
    for(int i = 0, j = text_len - 1; i < j; i++, j--)
    {
        char tmp = *(text + i);
        *(text + i) = *(text + j);
        *(text + j) = tmp;
    }
    return text;
}

char* remove_non_letters(char* text)
{
    if(text == NULL)
        return NULL;
    int i = 0;
    while(*(text + i) != '\0')
    {
        if(!is_letter(*(text + i)))
            *(text + i) = ' ';
        i++;
    }
    return text;
}

void trim_beginning(char* text)
{
    int  i = 0;
    while(*(text + i) == ' ')
        i++;
    if(!i)
        return;
    do
        *text = *(text + i);
    while(*(text++ + i) != '\0');
}

void trim_end(char* text)
{
    int text_len = my_strlen(text);
    int i = 0;
    while(*(text + text_len - 1 - i) == ' ')
        i++;
    *(text + text_len - i) = '\0';
}

char* trim(char* text)
{
    if(text == NULL)
        return NULL;
    trim_beginning(text);
    int i = 1;
    if(i >= my_strlen(text))
        return text;
    while(*(text + i) != '\0')
    {
        if(*(text + i - 1) == ' ' && *(text + i) == ' ')
            trim_beginning(text + i);
        i++;
    }
    trim_end(text);
    return text;
}

int main(void)
{
    printf("Wpisz zdanie:\n");
    char str[SIZE + 1];
    fgets(str, SIZE + 1, stdin);
    remove_non_letters(str);
    trim(str);
    if(my_strlen(str) == 0)
        printf("%s", "wohs ot gnihtoN");
    else 
    {
        reverse(str);
        printf("%s", str);
    }
    return 0;
}