#include "stack.h"
#define START_STACK_SIZE 5

int main(void)
{
    struct stack_t *stack;
    if(stack_init(&stack, START_STACK_SIZE) == 2)
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
            stack_free(stack);
            return 1;
        }
        if(inp == 1)
        {
            printf("Podaj liczbe ");
            int val = 0;
            if(scanf("%d", &val) != 1)
            {
                printf("Incorrect input");
                stack_free(stack);
                return 1;
            }
            if(stack_push(stack, val) == 2)
            {
                printf("Failed to allocate memory");
                stack_free(stack);
                return 8;
            }
        } else if(inp == 2)
        {
            if(stack->head == 0)
                printf("Stack is empty\n");
            else
                printf("%d\n", stack_pop(stack, NULL));
        } else if(inp == 3)
        {
            if(stack->head == 0)
                printf("Stack is empty\n");
            else
            {
                stack_display((const struct stack_t *)stack);
                printf("\n");
            }
        } else if(inp != 0)
            printf("Incorrect input data\n");
    }
    stack_free(stack);
    return 0;
}