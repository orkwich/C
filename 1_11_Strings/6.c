#include <stdio.h>
#define SIZE 1000

void clear()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int my_strlen(const char* str)
{
    if(str == NULL)
        return -1;
    int i = 0;
    while(*(str + i) != '\0')
        i++;
    return i;
}

char* my_strcat(char* dest, const char* src)
{
    if(dest == NULL || src == NULL)
        return NULL;
    char *tmp = dest;
    while(*tmp != '\0')
        tmp++;
    int i = 0;
    do
        *(tmp + i) = *(src + i);
    while(*(src + i++) != '\0');
    return dest;
}

char* my_strcpy(char* dest, const char* src)
{
    if(dest == NULL || src == NULL)
        return NULL;
    int i = 0;
    do
        *(dest + i) = *(src + i);
    while(*(src + i++) != '\0');
    return dest;
}

int main(void)
{
    printf("Wprowadz napis pierwszy: ");
    char txt1[SIZE + 1];
    int i = 0;
    while((*(txt1 + i) = getchar()) != '\n')
    {
        if(i == SIZE && *(txt1 + i) != '\n' && *(txt1 + i) != '\0') 
        {
            clear();
            break;
        }
        i++;
    }
    *(txt1 + i) = '\0';
    printf("Wprowadz napis drugi: ");
    char txt2[(SIZE * 2) + 1];
    i = 0;
    while((*(txt2 + i) = getchar()) != '\n' && *(txt2 + i) != '\0' && i != SIZE)
        i++;
    *(txt2 + i) = '\0';
    printf("%d %d\n", my_strlen(txt1), my_strlen(txt2));
    my_strcat(txt2, txt1);
    printf("%s\n", txt2);
    my_strcpy(txt2, txt1);
    printf("%s\n", txt2);
    return 0;
}