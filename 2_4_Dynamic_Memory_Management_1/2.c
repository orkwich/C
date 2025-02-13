#include <stdio.h>
#include <stdlib.h>
#define PI 3.141593

int main(void)
{
    float *pi_ptr = malloc(sizeof(float));
    if(pi_ptr == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    *pi_ptr = PI;
    printf("%.6f %p", *pi_ptr, (void *)pi_ptr);
    free(pi_ptr);
    return 0;
}