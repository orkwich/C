#include "stack.h"

int stack_push(struct stack_t **stack, char *value)
{
    if(stack == NULL || value == NULL)
        return 1;
    struct stack_t *new = malloc(sizeof(struct stack_t));
    if(new == NULL)
        return 2;
    new->sentence = value;
    new->prev = *stack;
    *stack = new;
    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code)
{
    if(stack == NULL || *stack == NULL || (*stack)->sentence == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    char *res = (*stack)->sentence;
    struct stack_t *tmp = (*stack)->prev;
    free(*stack);
    *stack = tmp;
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

void stack_destroy(struct stack_t **stack)
{
    if(stack == NULL || *stack == NULL)
        return;
    while(*stack != NULL)
    {
        struct stack_t *tmp = (*stack)->prev;
        free((*stack)->sentence);
        free(*stack);
        *stack = tmp;
    }
}

int stack_load(struct stack_t **stack, const char *filename)
{
    if(stack == NULL || filename == NULL || *stack != NULL)
        return 1;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 2;
    while(!feof(f))
    {
        int c = '\0';
        int len = 0;
        while((c = getc(f)) != EOF && c != (int)'.' && c != '\0')
            len++;
        if(c == (int)'\0' || c == EOF)
            break;
        len++;
        fseek(f, -len, SEEK_CUR);
        char *text = calloc(len + 1, sizeof(char));
        if(text == NULL)
        {
            stack_destroy(stack);
            fclose(f);
            return 3;
        }
        char last_c = '\0';
        fscanf(f, "%[^.]", text);
        fscanf(f, "%c", &last_c);
        if(last_c == '\0')
        {
            free(text);
            break;
        }
        *(text + len - 1) = last_c;
        if(stack_push(stack, text) == 2)
        {
            free(text);
            stack_destroy(stack);
            fclose(f);
            return 3;
        }
    }
    fclose(f);
    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename)
{
    if(stack == NULL || filename == NULL || stack->sentence == NULL)
        return 1;
    FILE *f = fopen(filename, "w");
    if(f == NULL)
        return 2;
    struct stack_t *tmp = (struct stack_t *)stack;
    while(tmp != NULL)
    {
        fprintf(f, "%s", tmp->sentence);
        tmp = tmp->prev;
    }
    fclose(f);
    return 0;
}