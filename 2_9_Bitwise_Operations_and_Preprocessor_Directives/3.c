#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SIZE 100

void show(const void* ptr, size_t count)
{
    if(ptr == NULL || count == 0)
        return;
    uint8_t *bytes = (uint8_t*)ptr;
    for(size_t i = 0; i < count; i++)
        printf("%02x ", *(bytes + i));
    printf("\n");
}

void inverse_bits(void* ptr, size_t offset, size_t count)
{
    if(ptr == NULL || count == 0)
        return;
    uint8_t *bytes = (uint8_t*)ptr;
    bytes += offset;
    for(size_t i = 0; i < count; i++)
        *(bytes + i) = ~*(bytes + i);
}

int main()
{
    char txt[SIZE + 1];
    printf("Podaj tekst: ");
    scanf("%100[ .,!?':;A-Za-z]", txt);
    size_t count = strlen(txt) + 1;
    show((const void *)txt, count);
    inverse_bits((void *)txt, 0, count);
    show((const void *)txt, count);
    return 0;
}
