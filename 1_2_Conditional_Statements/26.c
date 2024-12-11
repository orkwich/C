#include <stdio.h>

//A, E, I, O, U, Y
//a, e, i, o, u, y

int main(void) 
{
    printf("podaj znak: ");
    char character = '\0';
    switch(scanf("%c", &character))
    {
        case 1:
        {
            break;
        }
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    switch((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
    {
        case 1:
        {
            break;
        }
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    switch(character)
    {
        case 'A':
        {
            printf("vowel");
            break;
        }
        case 'E':
        {
            printf("vowel");
            break;
        }
        case 'I':
        {
            printf("vowel");
            break;
        }
        case 'O':
        {
            printf("vowel");
            break;
        }
        case 'U':
        {
            printf("vowel");
            break;
        }
        case 'Y':
        {
            printf("vowel");
            break;
        }
        case 'a':
        {
            printf("vowel");
            break;
        }
        case 'e':
        {
            printf("vowel");
            break;
        }
        case 'i':
        {
            printf("vowel");
            break;
        }
        case 'o':
        {
            printf("vowel");
            break;
        }
        case 'u':
        {
            printf("vowel");
            break;
        }
        case 'y':
        {
            printf("vowel");
            break;
        }
        default:
        {
            printf("consonant");
        }
    }
    return 0;
}