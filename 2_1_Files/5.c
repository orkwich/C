#include <stdio.h>

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char fname[31];
    scanf("%30s", fname);
    FILE *f = fopen(fname, "w");
    if(f == NULL)
    {
        printf("Couldn't create file");
        return 5;
    }
    for(int i = 0; i <= 100; i++)
        fprintf(f, "%d\n", i);
    fclose(f);
    printf("File saved\n");
    return 0;
}