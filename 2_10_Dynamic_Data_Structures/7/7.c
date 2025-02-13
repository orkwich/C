#include "linked_list.h"

int main(void)
{
    struct linked_list_t *list = ll_create();
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
            ll_clear(list);
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
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                if(ll_push_back(list, inp) == 2)
                {
                    printf("Failed to allocate memory");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            } case 2:
            {
                if(ll_is_empty((const struct linked_list_t *)list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("%d\n", ll_pop_back(list, NULL));
                break;
            } case 3:
            {
                printf("Podaj liczbe ");
                if(scanf("%d", &inp) != 1)
                {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                if(ll_push_front(list, inp) == 2)
                {
                    printf("Failed to allocate memory");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            } case 4:
            {
                if(ll_is_empty((const struct linked_list_t *)list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("%d\n", ll_pop_front(list, NULL));
                break;
            } case 5:
            {
                printf("Podaj liczbe ");
                if(scanf("%d", &inp) != 1)
                {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int res = ll_insert(list, idx, inp);
                if(res == 2)
                {
                    printf("Failed to allocate memory");
                    ll_clear(list);
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
                if(ll_is_empty((const struct linked_list_t *)list) == 1)
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int err = 0;
                int res = ll_remove(list, idx, &err);
                if(err == 1)
                {
                    printf("Index out of range\n");
                    continue;
                } else
                    printf("%d\n", res);
                break;
            } case 7:
            {
                if(ll_is_empty(list) == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", ll_back((const struct linked_list_t *)list, NULL));
                break;
            } case 8:
            {
                if(ll_is_empty(list) == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", ll_front((const struct linked_list_t *)list, NULL));
                break;
            } case 9:
            {
                printf("%d\n", ll_is_empty(list));
                break;
            } case 10:
            {
                printf("%d\n", ll_size(list));
                break;
            } case 11:
            {
                ll_clear(list);
                break;
            } case 12:
            {
                if(ll_is_empty(list))
                {
                    printf("List is empty\n");
                    continue;
                }
                printf("Podaj index ");
                unsigned int idx = 0;
                if(scanf("%u", &idx) != 1)
                {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                int err = 0;
                int res = ll_at(list, idx, &err);
                if(err == 1)
                {
                    printf("Index out of rang\n");
                    continue;
                }
                printf("%d\n", res);
                break;
            } case 13:
            {
                if(ll_is_empty(list))
                {
                    printf("List is empty\n");
                    continue;
                }
                ll_display(list);
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
    ll_clear(list);
    free(list);
    return 0;
}