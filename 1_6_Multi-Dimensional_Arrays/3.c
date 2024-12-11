#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50
#define SIZE 5

int** init_int_matrix(int rows, int columns)
{
    int **matrix = malloc(sizeof(int*) * rows);
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(sizeof(int) * columns);
        for(int j = 0; j < columns; j++)
            matrix[i][j] = 0;
    }
    return matrix;
}

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

int read_int_matrix(int **matrix, int rows, int columns)
{
    if(!rows || !columns)
        return -2;
    int i = 0;
    int j = 0;
    char *buff = malloc(sizeof(char) * BUFF_SIZE);
    while(j < columns && i < rows)
    {
        char tmp;
        while(isSpaceOrNewLine(tmp = getchar()));
        if(!isNumberOrSign(tmp))
        {
            free(buff);
            return -1;
        }
        int buffLen = 0;
        buff[buffLen++] = tmp;
        while(isNumberOrSign(buff[buffLen++] = getchar()));
        buffLen--;
        if(!isSpaceOrNewLine(buff[buffLen]))
        {
            free(buff);
            return -1;
        }
        buff[buffLen] = '\0';
        matrix[i][j++] = atoi(buff);
        if(j == columns)
        {
            i++;
            j = 0;
        }
    }
    free(buff);
    return 0;
}

void display_int_matrix(int **matrix, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main(void)
{
    printf("podaj liczby:\n");
    int **matrix = init_int_matrix(SIZE, SIZE);
    if(read_int_matrix(matrix, SIZE, SIZE) == -1)
    {
        printf("incorrect input");
        return 1;
    }
    for(int i = 0; i < SIZE; i++)
    {
        int j = SIZE - 1 - i;
        int tmp = matrix[i][i];
        matrix[i][i] = matrix[i][j];
        matrix[i][j] = tmp;
    }
    display_int_matrix(matrix, SIZE, SIZE);
    return 0;
}