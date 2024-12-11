#include <stdio.h>
#define SIZE 1000

char *my_strpbrk(const char *str1, const char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return NULL;
    int i = 0;
    while(*(str1 + i) != '\0')
    {
        int j = 0;
        while(*(str2 + j) != '\0')
            if(*(str1 + i) == *(str2 + j++))
                return (char*)str1 + i;
        i++;
    }
    return NULL;
}

int main(void)
{
    printf("Podaj tekst: ");
    char input[SIZE + 1];
    fgets(input, SIZE + 1, stdin);
    char vowels[13] = "AEIOUYaeiouy";
    char *tmp;
    int count = 0;
    tmp = my_strpbrk(input, vowels);
    while(tmp != NULL)
    {
        count++;
        tmp = my_strpbrk(tmp + 1, vowels);
    }
    printf("%d", count);
    return 0;
}