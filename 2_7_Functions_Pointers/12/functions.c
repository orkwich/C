#include "functions.h"

void print_chicken(void)
{
    printf(" MM\n<' \\___/|\n  \\_  _/\n    ][\n");
}

void print_egg(void)
{
    printf("  .~~~.\n /     \\\n(\\/\\/\\/\\)\n \\     /\n  `~~~`\n");
}

void print_rabbit(void)
{
    printf(" \\\\   //\n  )\\-/(\n  /o o\\\n ( =T= )\n /'---'\\\n");
}

void (**easter(int size, void (*chicken)(void), void (*egg)(void), void (*rabbit)(void)))(void)
{
    if(size <= 0 || chicken == NULL || egg == NULL || rabbit == NULL)
        return NULL;
    void (**funcs)(void) = malloc(sizeof(void (*)(void)) * size);
    if(funcs == NULL)
        return NULL;
    for(int i = 0; i < size; i++)
    {
        int r = rand() % 3;
        if(r == 0)
            *(funcs + i) = chicken;
        if(r == 1)
            *(funcs + i) = egg;
        if(r == 2)
            *(funcs + i) = rabbit;
    }
    return funcs;
}