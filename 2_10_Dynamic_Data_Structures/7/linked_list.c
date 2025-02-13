#include "linked_list.h"

struct linked_list_t* ll_create()
{
    struct linked_list_t *list = malloc(sizeof(struct linked_list_t));
    if(list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int ll_push_back(struct linked_list_t* ll, int value)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->next = NULL;
    if(ll->tail == NULL)
        ll->head = new;
    else
        ll->tail->next = new;
    ll->tail = new;
    return 0;
}

int ll_push_front(struct linked_list_t* ll, int value)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->next = NULL;
    if(ll->tail == NULL && ll->head == NULL)
        ll->tail = new;
    else
        new->next = ll->head;
    ll->head = new;
    return 0;
}

int ll_pop_front(struct linked_list_t* ll, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    int res = ll->head->data;
    struct node_t *tmp = ll->head;
    ll->head = ll->head->next;
    free(tmp);
    if(ll->head == NULL)
        ll->tail = NULL;
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

int ll_pop_back(struct linked_list_t* ll, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    int res = ll->tail->data;
    if(ll->head == ll->tail)
    {
        free(ll->tail);
        ll->tail = NULL;
        ll->head = NULL;
    } else
    {
        struct node_t *tmp = ll->head;
        while(tmp->next != ll->tail)
            tmp = tmp->next;
        free(ll->tail);
        ll->tail = tmp;
        ll->tail->next = NULL;
    }
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

int ll_back(const struct linked_list_t* ll, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(err_code != NULL)
        *err_code = 0;
    return ll->tail->data;
}

int ll_front(const struct linked_list_t* ll, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(err_code != NULL)
        *err_code = 0;
    return ll->head->data;
}

struct node_t* ll_begin(struct linked_list_t* ll)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return NULL;
    return ll->head;
}

struct node_t* ll_end(struct linked_list_t* ll)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return NULL;
    return ll->tail;
}

int ll_size(const struct linked_list_t* ll)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return -1;
    if(ll_is_empty(ll))
        return 0;
    int size = 1;
    struct node_t *tmp = ll->head;
    while(tmp != ll->tail)
    {
        tmp = tmp->next;
        size++;
    }
    return size;
}

int ll_is_empty(const struct linked_list_t* ll)
{
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->tail != NULL && ll->head == NULL))
        return -1;
    if(ll->head == NULL && ll->tail == NULL)
        return 1;
    return 0;
}

int ll_at(const struct linked_list_t* ll, unsigned int index, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    struct node_t *tmp = ll->head;
    for(unsigned int i = 0; i < index; i++)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            if(err_code != NULL)
                *err_code = 1;
            return 0;
        }
    }
    if(err_code != NULL)
        *err_code = 0;
    return tmp->data;
}

int ll_insert(struct linked_list_t* ll, unsigned int index, int value)
{
    if(ll == NULL)
        return 1;
    if(index == 0)
        return ll_push_front(ll, value);
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    struct node_t *tmp = ll->head;
    for(unsigned int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            free(new);
            return 1;
        }
    }
    new->next = tmp->next;
    tmp->next = new;
    if(new->next == NULL)
        ll->tail = new;
    return 0;
}

int ll_remove(struct linked_list_t* ll, unsigned int index, int *err_code)
{
    if(ll == NULL || ll->head == NULL || ll->tail == NULL || (int)index < 0)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    struct node_t *tmp = ll->head;
    if(index == 0)
    {
        int res = tmp->data;
        tmp = tmp->next;
        free(ll->head);
        ll->head = tmp;
        if(err_code != NULL)
            *err_code = 0;
        if(ll->head == NULL)
            ll->tail = NULL;
        return res;
    }
    for(unsigned int i = 0; i < index - 1; i++)
    {
        if(tmp == NULL)
        {
            if(err_code != NULL)
                *err_code = 1;
            return 0;
        }
        tmp = tmp->next;
    }
    if(tmp->next == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    struct node_t *tmp2 = tmp->next->next;
    int res = tmp->next->data;
    free(tmp->next);
    tmp->next = tmp2;
    if(tmp->next == NULL)
        ll->tail = tmp;
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

void ll_clear(struct linked_list_t* ll)
{
    if(ll == NULL)
        return;
    while(ll->head != NULL)
    {
        struct node_t *tmp = ll->head->next;
        free(ll->head);
        ll->head = tmp;
    }
    ll->tail = NULL;
}

void nodes_display(struct node_t *n)
{
    if(n != NULL)
    {
        printf("%d ", n->data);
        nodes_display(n->next);
    }
}

void ll_display(const struct linked_list_t* ll)
{
    if(ll == NULL)
        return;
    nodes_display(ll->head);
}