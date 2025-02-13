#include "stack.h"

int main(void)
{
    struct stack_t *stack;
    if(stack_init(&stack) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    int inp = -1;
    while(inp != 0)
    {
        printf("Co chcesz zrobic? ");
        if(scanf("%d", &inp) != 1)
        {
            printf("Incorrect input");
            stack_destroy(&stack);
            return 1;
        }
        if(inp == 1)
        {
            printf("Podaj liczbe ");
            int val = 0;
            if(scanf("%d", &val) != 1)
            {
                printf("Incorrect input");
                stack_destroy(&stack);
                return 1;
            }
            if(stack_push(stack, val) == 2)
            {
                printf("Failed to allocate memory");
                stack_destroy(&stack);
                return 8;
            }
        } else if(inp == 2)
            if(stack_empty(stack))
                printf("Stack is empty\n");
            else
                printf("%d\n", stack_pop(stack, NULL));
        else if(inp == 3)
            printf("%d\n", stack_empty(stack));
        else if(inp == 4)
            if(stack_empty(stack))
                printf("Stack is empty\n");
            else
            {
                stack_display((const struct stack_t *)stack);
                printf("\n");
            }
        else if(inp != 0)
            printf("Incorrect input data\n");
    }
    stack_destroy(&stack);
    return 0;
}