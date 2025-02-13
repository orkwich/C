#include <stdio.h>
//#define SIZE 30

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char filename[31];
    scanf("%30s", filename);
    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Couldn't open file");
        return 4;
    }
    char c = getc(file);
    if(c == EOF)
        printf("Nothing to show");
    else
        do
            printf("%c", c);
        while((c = getc(file)) != EOF);
    fclose(file);
    return 0;
}