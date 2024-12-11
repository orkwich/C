#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char* get_word(char* str)
{
    static char *static_str = NULL;
    static char buff[SIZE + 1];
    if(str == NULL && static_str == NULL)
        return NULL;
    if(str == NULL && static_str != NULL)
        str = (char*)static_str;
    while(*str != '\0' && !is_letter(*str))
        str++;
    int i = 0;
    while(*str != '\0' && is_letter(*str))
        *(buff + i++) = *str++;
    *(buff + i) = '\0';
    if(*str == '\0' && i == 0)
    {
        static_str = NULL;
        return NULL;
    }
    static_str = str;
    return buff;
}

int main(void)
{
    printf("Podaj tekst: ");
    char str[SIZE + 1];
    fgets(str, SIZE + 1, stdin);
    char *tmp = get_word(str);
    if(tmp == NULL)
        tmp = get_word("Nothing to show");
    do
        printf("%s\n", tmp);
    while((tmp = get_word(NULL)) != NULL);
    return 0;
}