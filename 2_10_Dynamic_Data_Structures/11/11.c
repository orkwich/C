#include "doubly_linked_list.h"

int main(void)
{
    struct doubly_linked_list_t *dll1 = dll_create();
    if(dll1 == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    struct doubly_linked_list_t *dll2 = dll_create();
    if(dll2 == NULL)
    {
        printf("Failed to allocate memory");
        free(dll1);
        return 8;
    }
    printf("Enter first list (-1 when done): ");
    int inp = 0;
    while(inp != -1)
    {
        if(scanf("%d", &inp) != 1)
        {
            printf("Incorrect input");
            dll_clear(dll1);
            free(dll1);
            free(dll2);
            return 1;
        }
        if(inp == -1)
            break;
        if(dll_push_back(dll1, inp) == 2)
        {
            printf("Failed to allocate memory");
            dll_clear(dll1);
            free(dll1);
            free(dll2);
            return 8;
        }
    }
    printf("Enter second list (-1 when done): ");
    inp = 0;
    while(inp != -1)
    {
        if(scanf("%d", &inp) != 1)
        {
            printf("Incorrect input");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 1;
        }
        if(inp == -1)
            break;
        if(dll_push_back(dll2, inp) == 2)
        {
            printf("Failed to allocate memory");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 8;
        }
    }
    if(dll_is_empty(dll1) == 1 && dll_is_empty(dll2) == 1)
    {
        printf("Not enough data available");
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        return 3;
    }
    printf("Choose method (0, 1 or 2): ");
    if(scanf("%d", &inp) != 1)
    {
        printf("Incorrect input");
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        return 1;
    }
    if(inp < 0 || inp > 2)
    {
        printf("Incorrect input data");
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        return 2;
    }
    if(inp == 0)
        dll_concat_zip(dll1, dll2);
    if(inp == 1)
        dll_concat_begin(dll1, dll2);
    if(inp == 2)
        dll_concat_end(dll1, dll2);
    dll_display(dll1);
    printf("\n");
    dll_display_reverse(dll1);
    dll_clear(dll1);
    dll_clear(dll2);
    free(dll1);
    free(dll2);
    return 0;
}