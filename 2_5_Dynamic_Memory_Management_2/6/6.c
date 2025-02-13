#include "matrix_utils.h"
#define FNAME_SIZE 19

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

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
    char *fname = malloc(sizeof(char) * (FNAME_SIZE + 1));
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pierwszego pliku: ");
    scanf("%19s", fname);
    clear();
    struct matrix_t *m1 = NULL;
    int err_code = 0;
    int format = check_format(fname);
    if(format == 1)
        m1 = matrix_load_t(fname, &err_code);
    if(format == 2)
        m1 = matrix_load_b(fname, &err_code);
    if(format == 0)
    {
        printf("Unsupported file format");
        free(fname);
        return 7;
    }
    if(err_code == 2)
    {
        printf("Couldn't open file");
        free(fname);
        return 4;
    }
    if(err_code == 3)
    {
        printf("File corrupted");
        free(fname);
        return 6;
    }
    if(err_code == 4)
    {
        printf("Failed to allocate memory");
        free(fname);
        return 8;
    }
    printf("Podaj nazwe drugiego pliku: ");
    scanf("%19s", fname);
    struct matrix_t *m2 = NULL;
    err_code = 0;
    format = check_format(fname);
    if(format == 1)
        m2 = matrix_load_t(fname, &err_code);
    if(format == 2)
        m2 = matrix_load_b(fname, &err_code);
    free(fname);
    if(format == 0)
    {
        printf("Unsupported file format");
        matrix_destroy_struct(&m1);
        return 7;
    }
    if(err_code == 2)
    {
        printf("Couldn't open file");
        matrix_destroy_struct(&m1);
        return 4;
    }
    if(err_code == 3)
    {
        printf("File corrupted");
        matrix_destroy_struct(&m1);
        return 6;
    }
    if(err_code == 4)
    {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&m1);
        return 8;
    }
    struct matrix_t *m3 = matrix_add(m1, m2);
    if(m3 == NULL)
        printf("Error\n");
    else
    {
        matrix_display(m3);
        matrix_destroy_struct(&m3);
    }
    m3 = matrix_subtract(m1, m2);
    if(m3 == NULL)
        printf("Error\n");
    else
    {
        matrix_display(m3);
        matrix_destroy_struct(&m3);
    }
    m3 = matrix_multiply(m1, m2);
    if(m3 == NULL)
        printf("Error\n");
    else
    {
        matrix_display(m3);
        matrix_destroy_struct(&m3);
    }
    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);
    return 0;
}