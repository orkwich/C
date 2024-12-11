#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Podaj imie:\n");
    char *name = malloc(sizeof(char) * 11);

    for(int i = 0; i < 11; i++)
        name[i] = '\0';

    scanf("%10s", name);

    while(*(name + 1) != '\0')
        name++;

    if(*name == 'a')
        printf("Imie zenskie");
    else
        printf("Imie meskie");

    free(name);
    return 0;
}