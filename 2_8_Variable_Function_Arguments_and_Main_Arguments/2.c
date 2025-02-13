#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define MAX_INP_COUNT 4
#define MAX_INP_LEN 1000

int concatenate(char *res, int size, int args, ...)
{
    if(res == NULL || size <= 0 || args <= 0)
        return 1;
    va_list argv;
    va_start(argv, args);
    int sum_size = 0;
    *res = '\0';
    for(int i = 0; i < args; i++)
    {
        char *tmp = va_arg(argv, char*);
        sum_size += (int)strlen(tmp);
        if(sum_size >= size)
        {
            va_end(argv);
            return 2;
        }
        if(i != 0)
        {
            sum_size += 1;
            if(sum_size >= size)
            {
                va_end(argv);
                return 2;
            }
            strcat(res, " ");
        }
        strcat(res, tmp);
    }
    return 0;
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
    char *res = malloc(sizeof(char) * (MAX_INP_COUNT * (MAX_INP_LEN + 1)));
    if(res == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    char **input = malloc(sizeof(char *) * MAX_INP_COUNT);
    if(input == NULL)
    {
        free(res);
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
            free(res);
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
        free(res);
        printf("Incorrect input");
        return 1;
    }
    if(n < 2 || n > 4)
    {
        free_input(input, MAX_INP_COUNT);
        free(res);
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
    concatenate(res, (MAX_INP_COUNT * (MAX_INP_LEN + 1)), n, *input, *(input + 1), *(input + 2), *(input + 3));
    printf("%s", res);
    free_input(input, MAX_INP_COUNT);
    free(res);
    return 0;
}