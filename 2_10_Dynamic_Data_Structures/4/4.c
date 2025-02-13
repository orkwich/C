#include "stack.h"

int main(int args, char **argv)
{
    if(args < 2)
    {
        printf("Not enough arguments");
        return 9;
    }
    for(int i = 1; i < args; i++)
    {
        struct stack_t *stack = NULL;
        int res = stack_load(&stack, *(argv + i));
        if(res == 2)
        {
            printf("Couldn't open file %s\n", *(argv + i));
            continue;
        }
        if(res == 3)
        {
            printf("Failed to allocate memory");
            stack_destroy(&stack);
            return 8;
        }
        if(stack_save(stack, *(argv + i)) == 2)
        {
            printf("Couldn't create file");
            stack_destroy(&stack);
            return 5;
        }
        printf("File %s saved\n", *(argv + i));
        stack_destroy(&stack);
    }
    return 0;
}