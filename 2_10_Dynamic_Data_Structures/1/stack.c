#include "stack.h"

int stack_init(struct stack_t **stack, int N)
{
    if(stack == NULL || N <= 0)
        return 1;
    *stack = malloc(sizeof(struct stack_t));
    if(*stack == NULL)
        return 2;
    (*stack)->data = malloc(sizeof(int) * N);
    if((*stack)->data == NULL)
    {
        stack_free(*stack);
        *stack = NULL;
        return 2;
    }
    (*stack)->capacity = N;
    (*stack)->head = 0;
    return 0;
}

int stack_push(struct stack_t *stack, int value)
{
    if(stack == NULL || stack->head > stack->capacity || stack->capacity <= 0 || stack->head < 0 || stack->data == NULL)
        return 1;
    if(stack->head == stack->capacity)
    {
        int *tmp = realloc(stack->data, stack->capacity * 2 * sizeof(int));
        if(tmp == NULL)
            return 2;
        stack->data = tmp;
        stack->capacity *= 2;
    }
    *(stack->data + stack->head++) = value;
    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if(stack == NULL || stack->head > stack->capacity || stack->capacity <= 0 || stack->head < 0 || stack->data == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(stack->head == 0)
    {
        if(err_code != NULL)
            *err_code = 2;
        return 0;
    }
    if(err_code != NULL)
        *err_code = 0;
    return *(stack->data + --stack->head);
}

void stack_display(const struct stack_t *stack)
{
    if(stack == NULL || stack->head > stack->capacity || stack->capacity <= 0 || stack->head < 0 || stack->head == 0 || stack->data == NULL)
        return;
    for(int i = stack->head - 1; i >= 0; i--)
        printf("%d ", *(stack->data + i));
}

void stack_free(struct stack_t *stack)
{
    if(stack == NULL)
        return;
    if(stack->data != NULL)
        free(stack->data);
    free(stack);
}