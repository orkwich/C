#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

double sum(const void* const buffer, int n)
{
    if(buffer == NULL || n <= 0)
        return -1;
    double sum = 0;
    int cur_pos = 0;
    for(int i = 0; i < n; i++)
    {
        sum += *(uint8_t*)((uint8_t*)buffer + cur_pos);
        cur_pos += sizeof(uint8_t);
        sum += *(uint16_t*)((uint8_t*)buffer + cur_pos);
        cur_pos += sizeof(uint16_t);
        sum += *(uint32_t*)((uint8_t*)buffer + cur_pos);
        cur_pos += sizeof(uint32_t);
        sum += *(double*)((uint8_t*)buffer + cur_pos);
        cur_pos += sizeof(double);
    }
    return sum;
}

int main()
{
    return 0;
}