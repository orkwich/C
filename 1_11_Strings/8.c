#include <stdio.h>
#define SIZE 1000

char change_size(char c)
{
    int diff = 'a' - 'A';
    if(c >= 'a' && c <= 'z')
        c -= diff;
    else if(c >= 'A' && c <= 'Z')
        c += diff;
    return c;
}

char* change_letter_size(char* dest, const char* src)
{
    if(dest == NULL || src == NULL)
        return NULL;
    int i = 0;
    do
    {
        *(dest + i) = change_size(*(src + i));
    } while(*(src + i++) != '\0');
    return dest;
}

int main(void)
{
    printf("Wpisz zdanie:\n");
    char str[SIZE + 1];
    fgets(str, SIZE + 1, stdin);
    char result[SIZE + 1];
    change_letter_size(result, str);
    printf("%s", result);
    return 0;
}