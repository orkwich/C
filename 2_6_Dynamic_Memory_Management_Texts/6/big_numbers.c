#include "big_numbers.h"

int validate(const char *number)
{
    if(number == NULL)
        return -1;
    int i = 0;
    if(*number == '-')
        i++;
    if((*(number + i) == '0' && strlen(number) > 1) || *(number + i) == '\0')
        return 2;
    int len = strlen(number + i);
    for(; i < len; i++)
        if(!isdigit(*(number + i)))
            return 2;
    if(i == 0)
        return 2;
    return 0;
}

int create(struct big_numbers_t *bn, int capacity)
{
    if(bn == NULL || capacity <= 0)
        return 1;
    bn->big_number = malloc(sizeof(char*) * capacity);
    if(bn->big_number == NULL)
        return 2;
    bn->size = 0;
    bn->capacity = capacity;
    return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity)
{
    if(bn == NULL || capacity <= 0)
        return 1;
    *bn = malloc(sizeof(struct big_numbers_t));
    if(*bn == NULL)
        return 2;
    if(create(*bn, capacity) == 2)
    {
        free(*bn);
        *bn = NULL;
        return 2;
    }
    return 0;
}

void destroy(struct big_numbers_t *bn)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
        return;
    for(int i = 0; i < bn->size; i++)
        free(*(bn->big_number + i));
    free(bn->big_number);
}

void destroy_big_numbers(struct big_numbers_t **bn)
{
    if(bn == NULL || *bn == NULL || (*bn)->size < 0 || (*bn)->capacity <= 0 || (*bn)->size > (*bn)->capacity || (*bn)->big_number == NULL)
        return;
    destroy(*bn);
    free(*bn);
    *bn = NULL;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || big_number == NULL || validate(big_number) == 2)
        return 1;
    if(bn->size == bn->capacity)
        return 3;
    *(bn->big_number + bn->size) = malloc(sizeof(char) * (strlen(big_number) + 1));
    if(*(bn->big_number + bn->size) == NULL)
        return 2;
    memcpy(*(bn->big_number + bn->size), big_number, strlen(big_number) + 1);
    bn->size++;
    return 0;
}

void display(const struct big_numbers_t *bn)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
        return;
    for(int i = 0; i < bn->size; i++)
        printf("%s\n", *(bn->big_number + i));
}