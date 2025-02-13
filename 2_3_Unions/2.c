#include <stdio.h>
#include "word_set.h"

int main(void)
{
    printf("Podaj liczbe: ");
    union word_set w;
    if(scanf("%d", &(w.x)) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    for(int i = 0; i < SIZE; i++)
        printf("%d ", (int)*(w.words + i));
    return 0;
}