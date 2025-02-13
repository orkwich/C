#include "big_numbers.h"
#define FNAME_SIZE 29

char* fname_sorted(char *fname)
{
    int len = strlen(fname) + strlen("_sorted");
    char *new_name = malloc(sizeof(char) * (len + 1));
    if(new_name == NULL)
        return NULL;
    char *extention = calloc(8, sizeof(char));
    if(extention == NULL)
    {
        free(new_name);
        return NULL;
    }
    int i = strlen(fname) - 1;
    while(i >= 0 && *(fname + i) != '.')
        i--;
    if(i > 0)
    {
        strcpy(extention, fname + i);
        *(fname + i) = '\0';
    }
    sprintf(new_name, "%s_sorted%s", fname, extention);
    free(extention);
    return new_name;
}

int main(void)
{
    char *fname = malloc(sizeof(char) * (FNAME_SIZE + 1));
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pliku: ");
    scanf("%29s", fname);
    struct big_numbers_t *bn;
    int res = load_big_numbers_b(&bn, fname);
    if(res == 2)
    {
        printf("Failed to allocate memory");
        free(fname);
        return 8;
    }
    if(res == 3)
    {
        printf("Couldn't open file");
        free(fname);
        return 4;
    }
    if(res == 4)
    {
        printf("File corrupted");
        free(fname);
        return 7;
    }
    sort_big_numbers_asc(bn);
    char *new_fname = fname_sorted(fname);
    free(fname);
    if(new_fname == NULL)
    {
        printf("Failed to allocate memory");
        destroy_big_numbers(&bn);
        return 8;
    }
    if(save_big_numbers_b(bn, new_fname) == 2)
        printf("Couldn't create file\n");
    else
        printf("File saved\n");
    free(new_fname);
    int err_code = 0;
    char *sum = total_sum_big_numbers(bn, &err_code);
    if(err_code)
        printf("Error");
    else
        printf("%s", sum);
    free(sum);
    destroy_big_numbers(&bn);
    return 0;
}