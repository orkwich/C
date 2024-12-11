#include <stdio.h>

int main(void)
{
    printf("podaj 5 liter: ");
    char letters[5];
    scanf("%c%c%c%c%c", &letters[0], &letters[1], &letters[2], &letters[3], &letters[4]);

    int difference = 'a' - 'A';
    if(letters[0] > 'Z')
        letters[0] -= difference;
    if(letters[1] > 'Z')
        letters[1] -= difference;
    if(letters[2] > 'Z')
        letters[2] -= difference;
    if(letters[3] > 'Z')
        letters[3] -= difference;
    if(letters[4] > 'Z')
        letters[4] -= difference;

    printf("%s\n", letters);

    return 0;
}