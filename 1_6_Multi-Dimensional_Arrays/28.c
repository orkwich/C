#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50
#define SIZE 10
#define FILTER 3

float** init_float_matrix(int rows, int columns)
{
    float **matrix = malloc(sizeof(float*) * rows);
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(sizeof(float) * columns);
        for(int j = 0; j < columns; j++)
            matrix[i][j] = 0;
    }
    return matrix;
}

int is_number_or_sign(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    if(c == '-' || c == '+' || c == '.')
        return 1;
    return 0;
}

int is_space_or_new_line(char c)
{
    if(c == ' ' || c == '\n')
        return 1;
    return 0;
}

int read_float_matrix(float **matrix, int rows, int columns)
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
        matrix[i][j++] = atof(buff);
        if(j == columns)
        {
            i++;
            j = 0;
        }
    }
    free(buff);
    return 0;
}

void display_float_matrix(float **matrix, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            printf("%.2f ", matrix[i][j]);
        printf("\n");
    }
}

float avg_of_matrix(float **matrix, int i, int j, int rows, int columns)
{
    float sum = 0;
    int elems = rows * columns;
    rows += i;
    columns += j;
    for(int ii = i; ii < rows; ii++)
        for(int jj = j; jj < columns; jj++)
            sum += matrix[ii][jj];
    return (float) sum / elems;
}

int main(void)
{
    printf("podaj liczbe:\n");
    float **matrix = init_float_matrix(SIZE, SIZE);
    int output = read_float_matrix(matrix, SIZE, SIZE);
    if(output == -1)
    {
        printf("incorrect input");
        return 1;
    }
    for(int i = 0; i < SIZE - 2; i++)
       for(int j = 0; j < SIZE - 2; j++)
           matrix[i][j] = avg_of_matrix(matrix, i, j, FILTER, FILTER);
    display_float_matrix(matrix, SIZE - 2, SIZE - 2);
    return 0;
}