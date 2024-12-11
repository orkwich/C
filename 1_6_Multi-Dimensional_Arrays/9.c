#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50
#define SIZE 10

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

int is_number_or_sign(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    if(c == '-' || c == '+')
        return 1;
    return 0;
}

int is_space_or_new_line(char c)
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
        while(is_space_or_new_line(tmp = getchar()));
        if(!is_number_or_sign(tmp))
        {
            free(buff);
            return -1;
        }
        int buffLen = 0;
        buff[buffLen++] = tmp;
        while(is_number_or_sign(buff[buffLen++] = getchar()));
        buffLen--;
        if(!is_space_or_new_line(buff[buffLen]))
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

int main(void)
{
    printf("podaj liczby:\n");
    int **matrix = init_int_matrix(SIZE, SIZE);
    int output = read_int_matrix(matrix, SIZE, SIZE);
    if(output == -1)
    {
        printf("incorrect input");
        return 1;
    }
    int sum_even = 0;
    int sum_odd = 0;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if((i + j) % 2)
                sum_odd += matrix[i][j];
            else
                sum_even += matrix[i][j];
    int result = sum_even - sum_odd;
    printf("%d", result);
    return 0;
}