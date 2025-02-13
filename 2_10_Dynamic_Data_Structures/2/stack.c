#include "stack.h"

int stack_init(struct stack_t **stack)
{
    if(stack == NULL)
        return 1;
    *stack = malloc(sizeof(struct stack_t));
    if(*stack == NULL)
        return 2;
    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value)
{
    if(stack == NULL)
        return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->next = stack->head;
    stack->head = new;
    return 0;
}

void stack_display(const struct stack_t *stack)
{
    if(stack_empty(stack))
        return;
    struct node_t *cur = stack->head;
    while(cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if(stack_empty(stack))
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    int val = stack->head->data;
    struct node_t *tmp = stack->head->next;
    free(stack->head);
    stack->head = tmp;
    if(err_code != NULL)
        *err_code = 0;
    return val;
}

void stack_destroy(struct stack_t **stack)
{
    if(stack == NULL)
        return;
    while((*stack)->head != NULL)
    {
        struct node_t *tmp = (*stack)->head->next;
        free((*stack)->head);
        (*stack)->head = tmp;
    }
    free(*stack);
    *stack = NULL;
}

int stack_empty(const struct stack_t *stack)
{
    if(stack == NULL)
        return 2;
    if(stack->head == NULL)
        return 1;
    return 0;
}