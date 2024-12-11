#include <stdio.h>
#define SIZE 1000

char* space_changer(char* str)
{
    if(str == NULL)
        return NULL;
    int i = 0;
    while(*(str + i) != '\0')
    {
        if(*(str + i) == ' ')
            *(str + i) = '_';
        i++;
    }
    return str;
}

int main(void)
{
    printf("Wpisz zdanie:\n");
    char str[SIZE + 1];
    fgets(str, SIZE + 1, stdin);
    space_changer(str);
    printf("%s", str);
    return 0;
}