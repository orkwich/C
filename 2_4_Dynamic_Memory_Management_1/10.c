#include "circular_buffer.h"

enum operation
{
    INIT = -1,
    END = 0,
    ADD,
    POPBACK,
    POPFRONT,
    PRINT,
    ISEMPTY,
    ISFULL
};

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    printf("Podaj rozmiar bufora: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t *cb;
    if(circular_buffer_create_struct(&cb, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    enum operation operation_code = INIT;
    while(operation_code)
    {
        printf("Co chcesz zrobic? ");
        int tmp = 0;
        if(scanf("%d", &tmp) != 1)
        {
            printf("Incorrect input");
            circular_buffer_destroy_struct(&cb);
            return 1;
        }
        clear();
        if(tmp < 0 || tmp > 6)
        {
            printf("Incorrect input data\n");
            continue;
        }
        operation_code = (enum operation)tmp;
        switch(operation_code)
        {
            case ADD:
            {
                printf("Podaj liczbe: ");
                int val = 0;
                if(scanf("%d", &val) != 1)
                {
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(&cb);
                    return 1;
                }
                clear();
                circular_buffer_push_back(cb, val);
                break;
            }
            case POPBACK:
            {
                if(circular_buffer_empty(cb))
                    printf("Buffer is empty\n");
                else
                    printf("%d\n", circular_buffer_pop_back(cb, NULL));
                break;
            }
            case POPFRONT:
            {
                if(circular_buffer_empty(cb))
                    printf("Buffer is empty\n");
                else
                    printf("%d\n", circular_buffer_pop_front(cb, NULL));
                break;
            }
            case PRINT:
            {
                if(circular_buffer_empty(cb))
                    printf("Buffer is empty\n");
                else
                    circular_buffer_display(cb);
                break;
            }
            case ISEMPTY:
            {
                printf("%d\n", circular_buffer_empty(cb));
                break;
            }
            case ISFULL:
            {
                printf("%d\n", circular_buffer_full(cb));
                break;
            }
            default:
                break;
        }
    }
    circular_buffer_destroy_struct(&cb);
    return 0;
}