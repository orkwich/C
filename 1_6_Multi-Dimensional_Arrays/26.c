#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50

typedef struct index
{
    int x;
    int y;
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
    int matrix1[10][10];

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            matrix1[i][j] = 0;
    
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
        matrix1[i][j++] = atoi(buff);
        if(j == 10)
        {
            i++;
            j = 0;
        }
        free(buff);
    }

    printf("podaj liczby:\n");
    int matrix2[2][2] = {{0, 0}, {0, 0}};
    i = 0;
    j = 0;
    while(j < 2 && i < 2)
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
        matrix2[i][j++] = atoi(buff);
        if(j == 2)
        {
            i++;
            j = 0;
        }
        free(buff);
    }

    int count = 0;
    idx indexes[100];
    for(i = 0; i < 100; i++)
    {
        indexes[i].x = 0;
        indexes[i].y = 0;
    }
    for(i = 0; i < 9; i++)
        for(j = 0; j < 9; j++)
        {
            if(matrix1[i][j] == matrix2[0][0] && matrix1[i + 1][j] == matrix2[1][0] && matrix1[i][j + 1] == matrix2[0][1] && matrix1[i + 1][j + 1] == matrix2[1][1])
            {
                indexes[count].x = i;
                indexes[count++].y = j;
            }
        }
    printf("%d\n", count);
    for(i = 0; i < count; i++)
        printf("%d %d\n", indexes[i].y, indexes[i].x);
    return 0;
}