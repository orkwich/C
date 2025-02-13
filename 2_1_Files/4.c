#include <stdio.h>

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

void fcopy_backwards(FILE *ffrom, FILE *fto)
{
    if(getc(ffrom) == EOF)
        return;
    int i = 0;
    do
    {
        fseek(ffrom, --i, SEEK_END);
        putc(getc(ffrom), fto);
    } while(ftell(ffrom) != 1);
}

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char filename[31];
    scanf("%30s", filename);
    FILE *ffrom;
    ffrom = fopen(filename, "rb");
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
    fcopy_backwards(ffrom, fto);
    printf("File copied\n");
    fclose(ffrom);
    fclose(fto);
    return 0;
}