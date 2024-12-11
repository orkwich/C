#include <stdio.h>
#define SIZE 1000

int is_uppercase(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int is_lowercase(char c)
{
    return (c >= 'a' && c <= 'z');
}

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int marks_counter(const char* text, int* uppercase, int* lowercase, int* whitespace)
{
    if(text == NULL || uppercase == NULL || lowercase == NULL || whitespace == NULL)
        return 1;
    int i = 0;
    (*uppercase) = 0;
    (*lowercase) = 0;
    (*whitespace) = 0;
    while(*(text + i) != '\0')
    {
        if(is_uppercase(*(text + i)))
            (*uppercase)++;
        if(is_lowercase(*(text + i)))
            (*lowercase)++;
        if(is_whitespace(*(text + i)))
            (*whitespace)++;
        i++;
    }
    return 0;
}

int main(void)
{
    printf("Podaj tekst: ");
    char input[SIZE + 1];
    int i = 0;
    while((*(input + i) = getchar()) != '\0' && *(input + i) != '\n' && i != SIZE)
        i++;
    *(input + i) = '\0';
    int uppercase = 0;
    int lowercase = 0;
    int whitespace = 0;
    marks_counter(input, &uppercase, &lowercase, &whitespace);
    printf("%d\n%d\n%d", uppercase, lowercase, whitespace);
    return 0;
}