#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

int* count_words(const char *filename, int *err_code, int N, ...)
{
    if(filename == NULL || N <= 0)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "r");
    if(f == NULL)
    {
        if(err_code != NULL)
            *err_code = 2;
        return NULL;
    }
    int *res = calloc(N, sizeof(int));
    if(res == NULL)
    {
        fclose(f);
        if(err_code != NULL)
            *err_code = 3;
        return NULL;
    }
    va_list args;
    va_start(args, N);
    for(int i = 0; i < N; i++)
    {
        char *tmp = va_arg(args, char*);
        int c = 0;
        int j = 0;
        while((c = fgetc(f)) != EOF)
        {
            if(!isalpha(c))
                continue;
            if(*(tmp + j) == (char)c)
                j++;
            else
            {
                j = 0;
                while((c = fgetc(f)) != EOF && isalpha(c));
                continue;
            }
            if(*(tmp + j) == '\0')
            {
                if(!isalpha(c = fgetc(f)))
                    (*(res + i))++;
                j = 0;
            }
        }
        fseek(f, 0, SEEK_SET);
    }
    va_end(args);
    fclose(f);
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

int main(int args, char **argv)
{
    if(args < 3)
    {
        printf("Not enough arguments");
        return 9;
    }
    int err;
    int *res = count_words(*(argv + 1), &err, args - 2, *(argv + 2), *(argv + 3), *(argv + 4), *(argv + 5), *(argv + 6), *(argv + 7), *(argv + 8), *(argv + 9), *(argv + 10), *(argv + 11), *(argv + 12), *(argv + 13), *(argv + 14), *(argv + 15), *(argv + 16), *(argv + 17), *(argv + 18), *(argv + 19), *(argv + 20));
    if(err == 2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(err == 3)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < args - 2; i++)
        printf("%d\n", *(res + i));
    free(res);
    return 0;
}