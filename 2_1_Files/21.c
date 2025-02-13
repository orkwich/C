#include <stdio.h>

int flast_number_space_index(FILE *f)
{
    int tmp = 0;
    char tmpc = '\0';
    while(fscanf(f, "%d%c", &tmp, &tmpc) > 0);
    tmp = ftell(f) - 1;
    fseek(f, 0, SEEK_SET);
    return tmp;
}

int flast_index(FILE *f)
{
    fseek(f, 0, SEEK_END);
    int tmp = ftell(f);
    fseek(f, 0, SEEK_SET);
    return tmp;
}

int is_file_corrupted(FILE *f)
{
    int tmp = 0;
    char tmpc = '\0';
    int last_idx = flast_index(f);
    int last_ns_idx = flast_number_space_index(f);
    if(last_ns_idx < 0)
        return 1;
    fseek(f, last_ns_idx, SEEK_SET);
    if(getc(f) != '\n')
        return 1;
    fseek(f, 0, SEEK_SET);
    while(fscanf(f, "%d%c", &tmp, &tmpc))
        if(tmp >= last_idx || tmp <= last_ns_idx)
            return 1;
    fseek(f, 0, SEEK_SET);
    return 0;
}

void fdecode(FILE *f)
{
    int tmp = 0;
    char tmpc = '\0';
    while(fscanf(f, "%d%c", &tmp, &tmpc))
    {
        int cur_pos = ftell(f);
        fseek(f, tmp, SEEK_SET);
        printf("%c", getc(f));
        fseek(f, cur_pos, SEEK_SET);
    }
}

int main(void)
{
    printf("Podaj siezke do pliku:\n");
    char fname[31];
    scanf("%30s", fname);
    FILE *f = fopen(fname, "r");
    if(f == NULL)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(is_file_corrupted(f))
    {
        fclose(f);
        printf("file corrupted");
        return 6;
    }
    fdecode(f);
    fclose(f);
    return 0;
}