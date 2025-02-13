#include "heap.h"
#include <stdio.h>
#include <unistd.h>
#define FENCE_SIZE 4
#define FENCE_VAL 0xF
#define CHUNK_SIZE sizeof(struct memory_chunk_t)

struct memory_manager_t manager = {0};

int is_chunk(struct memory_chunk_t *chunk)
{
    if(chunk == NULL)
        return 0;
    struct memory_chunk_t *ptr = manager.first_memory_chunk;
    while(ptr != chunk)
    {
        if(ptr == NULL)
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

void set_fences(struct memory_chunk_t *ptr)
{
    if(ptr == NULL)
        return;
    for(size_t i = 0; i < FENCE_SIZE; i++)
    {
        *((unsigned char*)ptr + i + CHUNK_SIZE) = FENCE_VAL;
        *((unsigned char*)ptr + i + CHUNK_SIZE + FENCE_SIZE + ptr->size) = FENCE_VAL;
    }
}

void chunk_fix(struct memory_chunk_t *chunk)
{
    if(chunk == NULL || chunk->next == NULL)
        return;
    size_t size = 0;
    struct memory_chunk_t *ptr = (struct memory_chunk_t*)((unsigned char*)(chunk + 1) + (FENCE_SIZE * 2) + chunk->size);
    while(((unsigned char*)ptr + size) != (unsigned char*)chunk->next)
        size++;
    chunk->size += size;
    set_fences(chunk);
}

void chunk_join(struct memory_chunk_t *c1, struct memory_chunk_t *c2)
{
    if(c1 == NULL || c2 == NULL)
        return;
    chunk_fix(c1);
    chunk_fix(c2);
    c1->next = c2->next;
    if(c2->next != NULL)
        c2->next->prev = c1;
    c1->size += c2->size + CHUNK_SIZE + (FENCE_SIZE * 2);
    set_fences(c1);
}

int heap_setup(void)
{
    manager.memory_size = 0;
    manager.first_memory_chunk = NULL;
    manager.is_setup = 1;
    return 0;
}

void heap_clean(void)
{
    intptr_t tmp = -(intptr_t)manager.memory_size;
    if(tmp < 0)
        sbrk(tmp);
    manager.first_memory_chunk = NULL;
    manager.memory_size = 0;
    manager.is_setup = 0;
}

void* heap_malloc(size_t size)
{
    if(!manager.is_setup || !size)
        return NULL;
    if(heap_validate())
        return NULL;
    struct memory_chunk_t *chunk = manager.first_memory_chunk;
    if(chunk != NULL)
    {
        while(chunk->next != NULL)
        {
            if(chunk->free && chunk->size >= size)
            {
                chunk->free = 0;
                chunk->size = size;
                set_fences(chunk);
                return ((unsigned char*)(chunk + 1)) + FENCE_SIZE;
            }
            chunk = chunk->next;
        }
    } else
    {
        chunk = (struct memory_chunk_t*)sbrk(CHUNK_SIZE + size + (FENCE_SIZE * 2));
        if(chunk == (void *)-1)
            return NULL;
        manager.first_memory_chunk = chunk;
        manager.memory_size += CHUNK_SIZE + size + (FENCE_SIZE * 2);
        chunk->prev = NULL;
        chunk->next = NULL;
        chunk->free = 0;
        chunk->size = size;
        set_fences(chunk);
        return (unsigned char*)chunk + CHUNK_SIZE + FENCE_SIZE;
    }
    struct memory_chunk_t *new = (struct memory_chunk_t*)sbrk(CHUNK_SIZE + size + (FENCE_SIZE * 2));
    if(new == (void*)-1)
        return NULL;
    chunk->next = new;
    manager.memory_size += CHUNK_SIZE + size + (FENCE_SIZE * 2);
    chunk->next->prev = chunk;
    chunk->next->next = NULL;
    chunk->next->size = size;
    chunk->next->free = 0;
    set_fences(chunk->next);
    return (unsigned char*)(chunk->next) + CHUNK_SIZE + FENCE_SIZE;
}

void* heap_calloc(size_t number, size_t size)
{
    void *ptr = heap_malloc(number * size);
    if(ptr == NULL)
        return NULL;
    for(size_t i = 0; i < number * size; i++)
        *((unsigned char*)ptr + i) = 0;
    return ptr;
}

size_t chunk_real_size(struct memory_chunk_t *chunk)
{
    if(chunk == NULL)
        return 0;
    if(chunk->next == NULL)
        return chunk->size;
    size_t real = chunk->size;
    while((unsigned char*)(chunk + 1) + (FENCE_SIZE * 2) + real != (unsigned char*)chunk->next)
        real++;
    return real;
}

void* heap_realloc(void* memblock, size_t count)
{
    if(!manager.is_setup)
        return NULL;
    if(memblock == NULL && count == 0)
        return NULL;
    if(memblock == NULL)
        return heap_malloc(count);
    struct memory_chunk_t *chunk = (struct memory_chunk_t*)((unsigned char*)((struct memory_chunk_t*)memblock - 1) - FENCE_SIZE);
    if(count == 0)
    {
        heap_free(memblock);
        return NULL;
    }
    if(get_pointer_type(memblock) != pointer_valid)
        return NULL;
    if(!is_chunk(chunk))
        return NULL;
    size_t real_size = chunk_real_size(chunk);
    while(real_size < count && chunk->next != NULL && chunk->next->free)
    {
        chunk_join(chunk, chunk->next);
        real_size = chunk->size;
    }
    if(real_size == count)
        return memblock;
    if(real_size > count)
    {
        if(chunk->next == NULL)
        {
            size_t diff = real_size - count;
            intptr_t shrink = -(intptr_t)(diff);
            sbrk(shrink);
            manager.memory_size -= diff;
        }
        chunk->size = count;
        set_fences(chunk);
    } else
    {
        if(chunk->next == NULL)
        {
            void *res = sbrk((intptr_t) (count - real_size));
            if (res == (void *) -1)
                return NULL;
            manager.memory_size += count - real_size;
            chunk->size = count;
            set_fences(chunk);
            return memblock;
        }
        unsigned char *new = heap_malloc(count);
        if(new == NULL)
            return NULL;
        for(size_t i = 0; i < chunk->size; i++)
            *(new + i) = *((unsigned char*)memblock + i);
        heap_free(memblock);
        return new;
    }
    return (unsigned char*)(chunk + 1) + FENCE_SIZE;
}

void heap_free(void* memblock)
{
    if(memblock == NULL || !manager.is_setup)
        return;
    struct memory_chunk_t *chunk = (struct memory_chunk_t *)((unsigned char *)memblock - FENCE_SIZE - CHUNK_SIZE);
    if(!is_chunk(chunk))
        return;
    chunk->free = 1;
    while(chunk->prev != NULL && chunk->prev->free)
    {
        chunk_join(chunk->prev, chunk);
        chunk = chunk->prev;
    }
    while(chunk->next != NULL && chunk->next->free)
        chunk_join(chunk, chunk->next);
    if(chunk->next == NULL)
    {
        size_t prev_to_free = 0;
        if(chunk->prev != NULL)
        {
            prev_to_free += chunk_real_size(chunk->prev) - chunk->prev->size;
            chunk->prev->next = NULL;
        } else
            manager.first_memory_chunk = NULL;
        intptr_t size = (intptr_t)(chunk->size + (FENCE_SIZE * 2) + CHUNK_SIZE + prev_to_free);
        sbrk((-size));
        manager.memory_size -= size;
        return;
    }
    chunk_fix(chunk);
}

size_t heap_get_largest_used_block_size(void)
{
    if(heap_validate())
        return 0;
    size_t max_size = 0;
    struct memory_chunk_t *chunk = manager.first_memory_chunk;
    while(chunk != NULL)
    {
        if(chunk->size > max_size && !chunk->free)
            max_size = chunk->size;
        chunk = chunk->next;
    }
    return max_size;
}

enum pointer_type_t get_pointer_type(const void* const pointer)
{
    if(pointer == NULL)
        return pointer_null;
    int valid = heap_validate();
    if(valid == 2)
        return pointer_unallocated;
    if(valid)
        return pointer_heap_corrupted;
    struct memory_chunk_t *ptr = manager.first_memory_chunk;
    while(ptr != NULL)
    {
        int j = 0;
        for(size_t i = 0; i < CHUNK_SIZE; i++)
            if(pointer == (unsigned char*)ptr + j++)
                return pointer_control_block;
        for(size_t i = 0; i < FENCE_SIZE; i++)
            if(pointer == (unsigned char*)ptr + j++)
            {
                if(ptr->free)
                    return pointer_unallocated;
                else
                    return pointer_inside_fences;
            }
        if(pointer == (unsigned char*)ptr + j)
        {
            if(ptr->free)
                return pointer_unallocated;
            else
                return pointer_valid;
        }
        for(size_t i = 0; i < ptr->size; i++)
            if(pointer == (unsigned char*)ptr + j++)
            {
                if(ptr->free)
                    return pointer_unallocated;
                else
                    return pointer_inside_data_block;
            }
        for(size_t i = 0; i < FENCE_SIZE; i++)
            if(pointer == (unsigned char*)ptr + j++)
            {
                if(ptr->free)
                    return pointer_unallocated;
                else
                    return pointer_inside_fences;
            }
        if(ptr->next != NULL)
            while((struct memory_chunk_t*)((unsigned char*)ptr + j) != (struct memory_chunk_t*)ptr->next)
                if((unsigned char*)ptr + j++ == pointer)
                    return pointer_unallocated;
        ptr = ptr->next;
    }
    return pointer_unallocated;
}

int heap_validate(void)
{
    if(!manager.is_setup)
        return 2;
    struct memory_chunk_t *chunk = manager.first_memory_chunk;
    if(chunk != NULL && chunk->prev != NULL)
        return 3;
    size_t sum_size = 0;
    while(chunk != NULL)
    {
        if(chunk->free != 0 && chunk->free != 1)
            return 3;
        size_t real_size = chunk->size;
        if(chunk->next != NULL)
        {
            if((FENCE_SIZE * 2) + CHUNK_SIZE + real_size >= manager.memory_size)
                return 3;
            while((unsigned char*)(chunk + 1) + (FENCE_SIZE * 2) + real_size != (unsigned char*)chunk->next)
            {
                real_size++;
                if(sum_size + real_size >= manager.memory_size)
                    return 3;
            }
            if(chunk != chunk->next->prev)
                return 3;
        }
        for(int i = 0; i < FENCE_SIZE; i++)
        {
            if(i + real_size + FENCE_SIZE + CHUNK_SIZE + sum_size >= manager.memory_size)
                return 3;
            if(*((unsigned char *)(chunk + 1) + i) != FENCE_VAL || *((unsigned char *)(chunk + 1) + i + chunk->size + FENCE_SIZE) != FENCE_VAL)
                return 1;
        }
        sum_size += real_size + CHUNK_SIZE + (FENCE_SIZE * 2);
        chunk = chunk->next;
    }
    if(sum_size != manager.memory_size)
        return 3;
    return 0;
}
