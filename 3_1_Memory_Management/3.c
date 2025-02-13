#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *concat_zip(const void* const float_buffer, const void * const int16_t_buffer, int size)
{
    if(float_buffer == NULL || int16_t_buffer == NULL || size <= 0)
        return NULL;
    uint8_t *res = malloc((sizeof(float) * size) + (sizeof(int16_t) * size));
    if(res == NULL)
        return NULL;
    int cur_pos = 0;
    for(int i = 0; i < size; i++)
    {
        *(float*)((uint8_t*)res + cur_pos) = *((float*)float_buffer + i);
        cur_pos += sizeof(float);
        *(int16_t*)((uint8_t*)res + cur_pos) = *((int16_t*)int16_t_buffer + i);
        cur_pos += sizeof(int16_t);
    }
    return (void*)res;
}

int main()
{
    return 0;
}