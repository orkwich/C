#include <stdio.h>

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

void fcopy(FILE *ffrom, FILE *fto)
{
    char c = EOF;
    while((c = getc(ffrom)) != EOF)
        putc(c, fto);
}

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char filename[31];
    scanf("%30s", filename);
    FILE *ffrom;
    ffrom = fopen(filename, "r");
    if(ffrom == NULL)
    {
        printf("Couldn't open file");
        return 4;
    }
    clear();
    printf("Podaj sciezke do pliku wyjsciowego:\n");
    scanf("%30s", filename);
    FILE *fto;
    fto = fopen(filename, "w");
    if(fto == NULL)
    {
        printf("Couldn't create file");
        fclose(ffrom);
        return 5;
    }
    fcopy(ffrom, fto);
    printf("File copied\n");
    fclose(ffrom);
    fclose(fto);
    return 0;
}