#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50

typedef struct index
{
    int x;
    int y;
    int direction;
}idx;

int isNumberOrSign(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    if(c == '-' || c == '+')
        return 1;
    return 0;
}

int isSpaceOrNewLine(char c)
{
    if(c == ' ' || c == '\n')
        return 1;
    return 0;
}

int main(void)
{
    int matrix[10][10];

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            matrix[i][j] = 0;
    
    printf("podaj liczby:\n");
    int i = 0;
    int j = 0;
    while(j < 10 && i < 10)
    {
        char tmp;
        while(isSpaceOrNewLine(tmp = getchar()));
        if(!isNumberOrSign(tmp))
        {
            printf("incorrect input");
            return 1;
        }
        char *buff = malloc(sizeof(char) * BUFF_SIZE);
        int buffLen = 0;
        buff[buffLen++] = tmp;
        while(isNumberOrSign(buff[buffLen++] = getchar()));
        buffLen--;
        if(!isSpaceOrNewLine(buff[buffLen]))
        {
            printf("incorrect input");
            free(buff);
            return 1;
        }
        buff[buffLen] = '\0';
        matrix[i][j++] = atoi(buff);
        if(j == 10)
        {
            i++;
            j = 0;
        }
        free(buff);
    }

    int maxSum = -__INT_MAX__;
    idx maxIndexes[200];
    int maxIndexesCount = 0;
    for(i = 0; i < 200; i++)
    {
        maxIndexes[i].x = 0;
        maxIndexes[i].y = 0;
        maxIndexes[i].direction = 0;
    }
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(j < 8)
            {
                int tmpSum = matrix[i][j] + matrix[i][j + 1] + matrix[i][j + 2];
                if(maxSum == tmpSum)
                {
                    maxIndexes[maxIndexesCount].x = i;
                    maxIndexes[maxIndexesCount].y = j;
                    maxIndexes[maxIndexesCount++].direction = 2;
                }
                if(maxSum < tmpSum)
                {
                    maxSum = tmpSum;
                    maxIndexesCount = 0;
                    maxIndexes[maxIndexesCount].x = i;
                    maxIndexes[maxIndexesCount].y = j;
                    maxIndexes[maxIndexesCount++].direction = 2;
                }
            }
            if(i < 8)
            {
                int tmpSum = matrix[i][j] + matrix[i + 1][j] + matrix[i + 2][j];
                if(maxSum == tmpSum)
                {
                    maxIndexes[maxIndexesCount].x = i;
                    maxIndexes[maxIndexesCount].y = j;
                    maxIndexes[maxIndexesCount++].direction = 1;
                }
                if(maxSum < tmpSum)
                {
                    maxSum = tmpSum;
                    maxIndexesCount = 0;
                    maxIndexes[maxIndexesCount].x = i;
                    maxIndexes[maxIndexesCount].y = j;
                    maxIndexes[maxIndexesCount++].direction = 1;
                }
            }
        }
    }
    printf("%d\n", maxSum);
    printf("%d\n", maxIndexesCount);
    for(i = 0; i < maxIndexesCount; i++)
        printf("%d %d %d\n", maxIndexes[i].direction, maxIndexes[i].x, maxIndexes[i].y);
    return 0;
}