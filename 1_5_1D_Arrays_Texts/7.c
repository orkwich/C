#include <stdio.h>

int main(void)
{
    printf("Podaj wyrazenie nawiasowe:\n");
    int i = 0;
    char tmp = '\0';
    int depth = 0;
    int maxDepth = 0;
    int indexes[25];
    int indexCount = 0;
    for(int j = 0; j < 25; j++)
        indexes[j] = 0;
    while((tmp = getchar()) != '\n')
    {
        if(i == 50)
        {
            printf("Input is too long");
            return 1;
        }
        if(tmp == '(')
            depth++;
        if(tmp == ')')
            depth--;
        if(maxDepth < depth)
        {
            maxDepth = depth;
            indexCount = 0;
        }
        if(maxDepth == depth)
            indexes[indexCount++] = i;
        i++;
    }
    printf("%d ", maxDepth);
    for(i = 0; i < indexCount; i++)
        printf("%d ", indexes[i]);
    return 0;
}