#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50

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

int readSquareMatrix(int **matrix, int size)
{
    int i = 0;
    int j = 0;
    while(j < size && i < size)
    {
        char tmp;
        while(isSpaceOrNewLine(tmp = getchar()));
        if(!isNumberOrSign(tmp))
            return 1;
        char *buff = malloc(sizeof(char) * BUFF_SIZE);
        int buffLen = 0;
        buff[buffLen++] = tmp;
        while(isNumberOrSign(buff[buffLen++] = getchar()));
        buffLen--;
        if(!isSpaceOrNewLine(buff[buffLen]))
        {
            free(buff);
            return 1;
        }
        buff[buffLen] = '\0';
        matrix[i][j++] = atoi(buff);
        if(j == size)
        {
            i++;
            j = 0;
        }
        free(buff);
    }
    return 0;
}

int main(void)
{
    int **matrix1 = malloc(sizeof(int*) * 5);
    int **matrix2 = malloc(sizeof(int*) * 5);;

    for(int i = 0; i < 5; i++)
    {
        matrix1[i] = malloc(sizeof(int) * 5);
        matrix2[i] = malloc(sizeof(int) * 5);
        for(int j = 0; j < 5; j++)
        {
            matrix1[i][j] = 0;
            matrix2[i][j] = 0;
        }
    }

    printf("podaj liczby:\n");
    if(readSquareMatrix(matrix1, 5))
    {
        printf("incorrect input");
        return 1;
    }
    printf("podaj liczby:\n");
    if(readSquareMatrix(matrix2, 5))
    {
        printf("incorrect input");
        return 1;
    }

    int indexes[5][6];
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 6; j++)
            indexes[i][j] = -1;
    
    for(int i = 0; i < 5; i++)
    {
        int indexCount = 0;
        for(int j = 0; j < 5; j++)
            for(int k = 0; k < 5; k++)
            {
                if(matrix1[i][k] != matrix2[k][j])
                {
                    break;
                }
                if(k == 4)
                    indexes[i][indexCount++] = j;
            }
    }
    for(int i = 0; i < 5; i++)
    {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", i);
        int j = 0;
        do
            printf("%d ", indexes[i][j++]);
        while(indexes[i][j] != -1);
        printf("\n");
    }
    return 0;
}