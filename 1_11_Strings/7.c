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

char* reverse(char* text, int len)
{
    if(text == NULL)
        return NULL;
    for(int i = 0, j = len - 1; i < j; i++, j--)
    {
        char tmp = *(text + i);
        *(text + i) = *(text + j);
        *(text + j) = tmp;
    }
    return text;
}

char* swap_order_words(char* txt)
{
    if(txt == NULL)
        return NULL;
    remove_non_letters(txt);
    trim(txt);
    reverse(txt, my_strlen(txt));
    char *tmp = txt;
    int j = 0;
    while(*(tmp + j) != '\0')
    {
        if(j)
            tmp += ++j;
        j = 0;
        while(*(tmp + j) != ' ' && *(tmp + j) != '\0')
            j++;
        reverse(tmp, j);
    }
    return txt;
}

int main(void)
{
    printf("Wpisz zdanie:\n");
    char str[SIZE + 1];
    fgets(str, SIZE + 1, stdin);
    swap_order_words(str);
    if(*str == '\0')
    {
        char tmp[SIZE + 1] = "Nothing to show";
        swap_order_words(tmp);
        printf("%s", tmp);
    }
    else
        printf("%s", str);
    return 0;
}