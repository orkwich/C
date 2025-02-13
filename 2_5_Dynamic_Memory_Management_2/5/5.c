#include "matrix_utils.h"
#define FNAME_SIZE 40

int check_format(char *filename)
{
    int len = strlen(filename);
    if(strcmp(filename + len - 4, ".txt") == 0)
        return 1;
    if(strcmp(filename + len - 4, ".bin") == 0)
        return 2;
    return 0;
}

int main(void)
{
    printf("Podaj wysokosc i szerokosc: ");
    int height = 0;
    int width = 0;
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(width <= 0 || height <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct matrix_t *m = matrix_create_struct(width, height);
    if(m == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartosci: ");
    if(matrix_read(m) == 2)
    {
        printf("Incorrect input");
        matrix_destroy_struct(&m);
        return 1;
    }
    char *fname = malloc(sizeof(char) * FNAME_SIZE);
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&m);
        return 8;
    }
    printf("Podaj sciezke do pliku:\n");
    scanf("%39s", fname);
    int fformat = 0;
    if((fformat = check_format(fname)) == 0)
    {
        printf("Unsupported file format");
        free(fname);
        matrix_destroy_struct(&m);
        return 7;
    }
    struct matrix_t *mt = matrix_transpose(m);
    if(mt == NULL)
    {
        printf("Failed to allocate memory");
        free(fname);
        matrix_destroy_struct(&m);
        return 8;
    }
    if(fformat == 1)
    {
        if(matrix_save_t(mt, fname) == 2)
        {
            printf("Couldn't create file");
            free(fname);
            matrix_destroy_struct(&m);
            matrix_destroy_struct(&mt);
            return 5;
        }
    }
    if(fformat == 2)
    {
        if(matrix_save_b(mt, fname) == 2)
        {
            printf("Couldn't create file");
            free(fname);
            matrix_destroy_struct(&m);
            matrix_destroy_struct(&mt);
            return 5;
        }
    }
    printf("File saved");
    free(fname);
    matrix_destroy_struct(&m);
    matrix_destroy_struct(&mt);
    return 0;
}