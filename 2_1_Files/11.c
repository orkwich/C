#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FNAME_SIZE 30
#define TAB_SIZE 100

void generate_tab(float *tab, int size)
{
    if(tab == NULL)
        return;
    srand(time(NULL));
    for(int i = 0; i < size; i++)
        *(tab + i) = (((float)rand() / RAND_MAX) * 200) - 100;
}

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char fname[FNAME_SIZE + 1];
    scanf("%30s", fname);
    FILE *f = fopen(fname, "wb");
    if(f == NULL)
    {
        printf("Couldn't create file");
        return 5;
    }
    float tab[TAB_SIZE];
    generate_tab(tab, TAB_SIZE);
    fwrite(tab, sizeof(float), TAB_SIZE, f);
    fclose(f);
    printf("File saved\n");
    return 0;
}