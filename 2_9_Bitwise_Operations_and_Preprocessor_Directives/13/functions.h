#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdint.h>

#define DISPLAY_BITS(value) \
    for(size_t i = 0; i < sizeof((value)) * 8; i++) \
        printf("%d", (int)!!(((uint64_t)1 << (((sizeof((value)) * 8) - 1) - i)) & (value))) \

#define REVERSE_BITS(ptr) \
    { \
        uint64_t tmp = (uint64_t)*ptr; \
        *ptr = 0; \
        for(size_t i = 0; i < sizeof(*ptr) * 8; i++) \
        { \
            if(tmp & ((uint64_t)1 << i)) \
                (*ptr) |= (uint64_t)1 << ((sizeof(*ptr) * 8) - 1 - i); \
        } \
    }

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) \
    (*pointer_to_bits_set_counter) = 0; \
    (*pointer_to_bits_cleared_counter) = 0; \
    for(size_t i = 0; i < sizeof((value)) * 8; i++) \
    { \
        if((value) & ((uint64_t)1 << i)) \
            (*pointer_to_bits_set_counter)++; \
        if((~(value)) & ((uint64_t)1 << i)) \
            (*pointer_to_bits_cleared_counter)++; \
    }

#endif