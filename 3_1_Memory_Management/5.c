#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct memory_manager_t
{
  void *memory_start;
  size_t memory_size;
  struct memory_chunk_t *first_memory_chunk;
};

struct memory_chunk_t
{
   struct memory_chunk_t* prev;
   struct memory_chunk_t* next;
   size_t size;
   int free;
};

struct memory_manager_t memory_manager = {0};

void memory_init(void *address, size_t size)
{
    if(address == NULL || size == 0)
        return;
    memory_manager.memory_start = address;
    memory_manager.memory_size = size;
    memory_manager.first_memory_chunk = NULL;
}

void *memory_malloc(size_t size)
{
    if(size == 0 || size > memory_manager.memory_size)
        return NULL;
    void *start;
    if(memory_manager.first_memory_chunk == NULL)
    {
        if(size + sizeof(struct memory_chunk_t) > memory_manager.memory_size)
            return NULL;
        start = memory_manager.memory_start;
        memory_manager.first_memory_chunk = start;
        ((struct memory_chunk_t*)start)->prev = NULL;
    } else
    {
        struct memory_chunk_t *cur = memory_manager.first_memory_chunk;
        int cur_size = sizeof(struct memory_chunk_t) + cur->size;
        while(!(cur->free && cur->size >= size) && cur->next != NULL)
        {
            cur = cur->next;
            cur_size += sizeof(struct memory_chunk_t) + cur->size;
        }
        if(cur->next == NULL)
        {
            if(cur_size + sizeof(struct memory_chunk_t) + size > memory_manager.memory_size)
                return NULL;
            start = (uint8_t*)cur + sizeof(struct memory_chunk_t) + cur->size;
            cur->next = start;
            ((struct memory_chunk_t*)start)->prev = cur;
        } else
        {
            cur->free = 0;
            cur->size = size;
            return (void*)((uint8_t*)cur + sizeof(struct memory_chunk_t));
        }
    }
    ((struct memory_chunk_t*)start)->next = NULL;
    ((struct memory_chunk_t*)start)->free = 0;
    ((struct memory_chunk_t*)start)->size = size;
    return (void*)((uint8_t*)start + sizeof(struct memory_chunk_t));
}

void memory_free(void *address)
{
    if(address == NULL)
        return;
    struct memory_chunk_t *to_free = memory_manager.first_memory_chunk;
    struct memory_chunk_t *to_merge_prev = NULL;
    int prev_size = 0;
    while((uint8_t*)to_free != (uint8_t*)address - sizeof(struct memory_chunk_t))
    {
        if(to_free == NULL)
            return;
        if(to_free->free && to_merge_prev == NULL)
        {
            to_merge_prev = to_free;
            prev_size += sizeof(struct memory_chunk_t) + to_merge_prev->size;
        }
        if(!to_free->free)
        {
            to_merge_prev = NULL;
            prev_size = 0;
        }
        to_free = to_free->next;
    }
    to_free->free = 1;
    struct memory_chunk_t *to_merge_next = to_free;
    int next_size = 0;
    while(to_merge_next->next != NULL && to_merge_next->next->free)
    {
        to_merge_next = to_merge_next->next;
        next_size += sizeof(struct memory_chunk_t) + to_merge_next->size;
    }
    if(to_merge_prev != NULL)
    {
        to_merge_prev->next = to_free->next;
        to_merge_prev->size = to_free->size + prev_size;
        to_free = to_merge_prev;
    }
    if(to_merge_next != to_free)
        if(to_merge_next->next != NULL)
        {
            to_free->next = to_merge_next->next;
            to_free->size += next_size;
        } else
            if(to_free->prev != NULL)
                to_free->prev->next = NULL;
            else
            {
                memory_init(memory_manager.memory_start, memory_manager.memory_size);
                return;
            }
    if(to_free->next == NULL && to_free->prev == NULL)
    {
        memory_init(memory_manager.memory_start, memory_manager.memory_size);
        return;
    }
    if(to_free->next == NULL)
        return;
    uint8_t *tmp = (uint8_t*)to_free;
    while((uint8_t*)tmp + sizeof(struct memory_chunk_t) + to_free->size != (uint8_t*)to_free->next)
        to_free->size++;
}

int main()
{
    int mem[1000];
    memory_init((void*)mem, 1000);
    int *arr = memory_malloc((size_t)100);
    for(int  i = 0; i < 100; i++)
        *(arr + i) = i;
    for(int  i = 0; i < 100; i++)
        printf("%d ", *(arr + i));
    memory_free(arr);
    return 0;
}