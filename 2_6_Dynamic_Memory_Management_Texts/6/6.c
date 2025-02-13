#include "big_numbers.h"
#define ELEMS_COUNT 10
#define BUFF_SIZE 200

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    struct big_numbers_t *bn;
    if(create_big_numbers(&bn, ELEMS_COUNT) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    char *buf = calloc(BUFF_SIZE + 1, sizeof(char));
    if(buf == NULL)
    {
        destroy_big_numbers(&bn);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    while(1)
    {
        int c;
        if((c = getc(stdin)) == (int)'\n')
            break;
        else
            ungetc(c, stdin);
        scanf("%200s", buf);
        int ret = add_big_number(bn, buf);
        if(ret == 1)
            printf("Incorrect input\n");
        if(ret == 2)
        {
            printf("Failed to allocate memory\n");
            break;
        }
        if(ret == 3)
        {
            printf("Buffer is full\n");
            break;
        }
        clear();
    }
    free(buf);
    if(bn->size != 0)
        display(bn);
    else
        printf("Buffer is empty");
    destroy_big_numbers(&bn);
    return 0;
}