#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define MAX_INP_COUNT 4
#define MAX_INP_LEN 1000

char* concatenate(int args, ...)
{
    if(args <= 0)
        return NULL;
    va_list argv;
    va_start(argv, args);
    char *res = NULL;
    for(int i = 0; i < args; i++)
    {
        char *tmp = va_arg(argv, char*);
        if(i != 0)
        {
            char *tmp_res = realloc(res, strlen(tmp) + 2 + strlen(res));
            if(tmp_res == NULL)
            {
                free(res);
                va_end(argv);
                return NULL;
            }
            res = tmp_res;
            strcat(res, " ");
        } else
        {
            res = calloc(strlen(tmp) + 1, sizeof(char));
            if(res == NULL)
            {
                va_end(argv);
                return NULL;
            }
        }
        strcat(res, tmp);
    }
    return res;
}

void free_input(char **inp, int size)
{
    if(inp == NULL || size <= 0)
        return;
    for(int i = 0; i < size; i++)
        free(*(inp + i));
    free(inp);
}

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    char **input = malloc(sizeof(char *) * MAX_INP_COUNT);
    if(input == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < MAX_INP_COUNT; i++)
    {
        *(input + i) = calloc((MAX_INP_LEN + 1), sizeof(char));
        if(*(input + i) == NULL)
        {
            for(--i; i >= 0; i--)
                free(*(input + i));
            free(input);
            printf("Failed to allocate memory");
            return 8;
        }
    }
    printf("Podaj liczbe tekstow do wprowadzenia: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        free_input(input, MAX_INP_COUNT);
        printf("Incorrect input");
        return 1;
    }
    if(n < 2 || n > 4)
    {
        free_input(input, MAX_INP_COUNT);
        printf("Incorrect input data");
        return 2;
    }
    clear();
    printf("Podaj teksty: ");
    for(int i = 0; i < n; i++)
    {
        fgets(*(input + i), MAX_INP_LEN + 1, stdin);
        if(*(*(input + i) + (strlen(*(input + i)) - 1)) == '\n')
            *(*(input + i) + (strlen(*(input + i)) - 1)) = '\0';
        else
            clear();
    }
    char *res = concatenate(n, *input, *(input + 1), *(input + 2), *(input + 3));
    free_input(input, MAX_INP_COUNT);
    if(res == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("%s", res);
    free(res);
    return 0;
}