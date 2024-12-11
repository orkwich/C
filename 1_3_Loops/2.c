#include <stdio.h>

int main(void)
{
    int i = 100;
    do
    {
        printf("%d ", i--);
    } while(i >= 0);
    
    return 0;
}