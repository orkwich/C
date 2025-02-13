#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create()
{
    return calloc(1, sizeof(struct doubly_linked_list_t));
}

int dll_push_back(struct doubly_linked_list_t* dll, int value)
{
    if(dll == NULL)
        return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->next = NULL;
    if(dll->head == NULL)
    {
        new->prev = NULL;
        dll->head = new;
    } else
    {
        new->prev = dll->tail;
        dll->tail->next = new;
    }
    dll->tail = new;
    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value)
{
    if(dll == NULL)
        return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->prev = NULL;
    if(dll->head == NULL)
    {
        new->next = NULL;
        dll->tail = new;
    } else
    {
        new->next = dll->head;
        dll->head->prev = new;
    }
    dll->head = new;
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    int res = dll->head->data;
    struct node_t *tmp = dll->head;
    dll->head = dll->head->next;
    if(dll->head != NULL)
        dll->head->prev = NULL;
    else
        dll->tail = NULL;
    free(tmp);
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    int res = dll->tail->data;
    struct node_t *tmp = dll->tail;
    dll->tail = dll->tail->prev;
    if(dll->tail != NULL)
        dll->tail->next = NULL;
    else
        dll->head = NULL;
    free(tmp);
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(err_code != NULL)
        *err_code = 0;
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(err_code != NULL)
        *err_code = 0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
        return NULL;
    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
        return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
        return -1;
    int count = 0;
    struct node_t *tmp = (struct node_t *)dll->head;
    while(tmp != NULL)
    {
        tmp = tmp->next;
        count++;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
        return -1;
    if(dll->head == NULL && dll->tail == NULL)
        return 1;
    return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if(dll == NULL || dll->head == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    struct node_t *tmp = dll->head;
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

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value)
{
    if(dll == NULL)
        return 1;
    if(index == 0)
        return dll_push_front(dll, value);
    struct node_t *tmp = dll->head;
    for(unsigned int i = 0; i < index; i++)
    {
        if(tmp == NULL)
            return 1;
        tmp = tmp->next;
    }
    if(tmp == NULL)
        return dll_push_back(dll, value);
    struct node_t *new = malloc(sizeof(struct node_t));
    if(new == NULL)
        return 2;
    new->data = value;
    new->next = tmp;
    new->prev = tmp->prev;
    tmp->prev->next = new;
    tmp->prev = new;
    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return 0;
    }
    if(index == 0)
        return dll_pop_front(dll, err_code);
    struct node_t *tmp = dll->head;
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
    if(tmp->next == NULL)
        return dll_pop_back(dll, err_code);
    int res = tmp->data;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);
    if(err_code != NULL)
        *err_code = 0;
    return res;
}

void dll_clear(struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
        return;
    struct node_t *tmp = dll->head;
    while(tmp != NULL)
    {
        tmp = tmp->next;
        free(dll->head);
        dll->head = tmp;
    }
    dll->tail = NULL;
}

void display_nodes(struct node_t *node)
{
    if(node != NULL)
    {
        printf("%d ", node->data);
        display_nodes(node->next);
    }
}

void dll_display(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
        return;
    display_nodes(dll->head);
}

void display_nodes_reverse(struct node_t *node)
{
    if(node != NULL)
    {
        printf("%d ", node->data);
        display_nodes_reverse(node->prev);
    }
}

void dll_display_reverse(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail == NULL)
        return;
    display_nodes_reverse(dll->tail);
}