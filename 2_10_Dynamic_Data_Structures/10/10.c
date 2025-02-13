#include "doubly_linked_list.h"

int main(void)
{
    struct doubly_linked_list_t *list = dll_create();
    if(list == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    int inp = -1;
    while(inp)
    {
        printf("Co chcesz zrobic? ");
        if(scanf("%d", &inp) != 1)
        {
            printf("Incorrect input");
            dll_clear(list);
            free(list);
            return 1;
        }
        if(inp == 0)
            break;
        switch(inp)
        {
            case 1:
            {
                printf("Podaj liczbe ");
                if(scanf("%d", &inp) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                if(dll_push_back(list, inp) == 2)
                {
                    printf("Failed to allocate memory");
                    dll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            } case 2:
            {
                if(dll_is_empty((const struct doubly_linked_list_t *)list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("%d\n", dll_pop_back(list, NULL));
                break;
            } case 3:
            {
                printf("Podaj liczbe ");
                if(scanf("%d", &inp) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                if(dll_push_front(list, inp) == 2)
                {
                    printf("Failed to allocate memory");
                    dll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            } case 4:
            {
                if(dll_is_empty((const struct doubly_linked_list_t *)list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("%d\n", dll_pop_front(list, NULL));
                break;
            } case 5:
            {
                printf("Podaj liczbe ");
                if(scanf("%d", &inp) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                int res = dll_insert(list, idx, inp);
                if(res == 2)
                {
                    printf("Failed to allocate memory");
                    dll_clear(list);
                    free(list);
                    return 8;
                }
                if(res == 1)
                {
                    printf("Index out of range\n");
                    continue;
                }
                break;
            } case 6:
            {
                if(dll_is_empty((const struct doubly_linked_list_t *)list) == 1)
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                int err = 0;
                int res = dll_remove(list, idx, &err);
                if(err == 1)
                {
                    printf("Index out of range\n");
                    continue;
                } else
                    printf("%d\n", res);
                break;
            } case 7:
            {
                if(dll_is_empty(list) == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", dll_back((const struct doubly_linked_list_t *)list, NULL));
                break;
            } case 8:
            {
                if(dll_is_empty(list) == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", dll_front((const struct doubly_linked_list_t *)list, NULL));
                break;
            } case 9:
            {
                printf("%d\n", dll_is_empty(list));
                break;
            } case 10:
            {
                printf("%d\n", dll_size(list));
                break;
            } case 11:
            {
                dll_clear(list);
                break;
            } case 12:
            {
                if(dll_is_empty(list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                int err = 0;
                int res = dll_at(list, idx, &err);
                if(err == 1)
                {
                    printf("Index out of rang\n");
                    continue;
                }
                printf("%d\n", res);
                break;
            } case 13:
            {
                if(dll_is_empty(list))
                {
                    printf("List is empty\n");
                    continue;
                }
                dll_display(list);
                printf("\n");
                break;
            } case 14:
            {
                if(dll_is_empty(list))
                {
                    printf("List is empty\n");
                    continue;
                }
                dll_display_reverse(list);
                printf("\n");
                break;
            } default:
            {
                printf("Incorrect input data\n");
                break;
            }
        }
        inp = -1;
    }
    dll_clear(list);
    free(list);
    return 0;
}