#include <stdio.h>

int is_file_existing(char *filename)
{
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 0;
    fclose(f);
    return 1;
}

int read_file(const char *filename)
{
    if(filename == NULL)
        return -1;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 0;
    char fname[31];
    int count = 1;
    while(fscanf(f, "%30s", fname) == 1)
    {
        printf("%s\n", fname);
        if(is_file_existing(fname))
            count += read_file(fname);
    }
    fclose(f);
    return count;
}

int main(void)
{
    printf("Podaj sciezke do pliku:\n");
    char filename[31];
    scanf("%30s", filename);
    if(!is_file_existing(filename))
    {
        printf("Couldn't open file");
        return 4;
    }
    printf("%d\n", read_file(filename));
    return 0;
}