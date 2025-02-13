#ifndef HEAP_H
#define HEAP_H
#include <stddef.h>

enum pointer_type_t
{
    pointer_null,//0
    pointer_heap_corrupted,//1
    pointer_control_block,//2
    pointer_inside_fences,//3
    pointer_inside_data_block,//4
    pointer_unallocated,//5
    pointer_valid//6
};

struct memory_manager_t
{
    size_t memory_size;
    struct memory_chunk_t *first_memory_chunk;
    unsigned char is_setup;
};

struct memory_chunk_t
{
    struct memory_chunk_t* prev;
    struct memory_chunk_t* next;
    size_t size;
    size_t free;
};

int heap_setup(void);
void heap_clean(void);
void* heap_malloc(size_t size);
void* heap_calloc(size_t number, size_t size);
void* heap_realloc(void* memblock, size_t count);
void heap_free(void* memblock);
size_t heap_get_largest_used_block_size(void);
enum pointer_type_t get_pointer_type(const void* const pointer);
int heap_validate(void);

#endif