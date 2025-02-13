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

int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(dll1 == NULL || dll2 == NULL)
        return 1;
    if(dll1->head == NULL && dll1->tail == NULL)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    if(dll2->head == NULL && dll2->tail == NULL)
        return 0;
    struct node_t *tmp_dll1 = dll1->head;
    struct node_t *tmp_dll2 = dll2->head;
    while(tmp_dll1 != NULL && tmp_dll2 != NULL)
    {
        struct node_t *tmp1 = tmp_dll1->next;
        struct node_t *tmp2 = tmp_dll2->next;
        tmp_dll1->next = tmp_dll2;
        if(tmp1 != NULL)
        {
            tmp1->prev = tmp_dll2;
            tmp_dll2->next = tmp1;
        }
        tmp_dll2->prev = tmp_dll1;
        if(tmp1 == NULL)
            dll1->tail = dll2->tail;
        tmp_dll1 = tmp1;
        tmp_dll2 = tmp2;
    }
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}

int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(dll1 == NULL || dll2 == NULL)
        return 1;
    if(dll1->head == NULL && dll1->tail == NULL)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    if(dll2->head == NULL && dll2->tail == NULL)
        return 0;
    dll2->tail->next = dll1->head;
    dll1->head->prev = dll2->tail;
    dll1->head = dll2->head;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}

int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2)
{
    if(dll1 == NULL || dll2 == NULL)
        return 1;
    if(dll1->head == NULL && dll1->tail == NULL)
    {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    if(dll2->head == NULL && dll2->tail == NULL)
        return 0;
    dll1->tail->next = dll2->head;
    dll2->head->prev = dll1->tail;
    dll1->tail = dll2->tail;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}
