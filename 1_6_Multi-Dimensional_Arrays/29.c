#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 50
#define MATRIX_SIZE 7
#define VEC_SIZE 4
#define STOP 0

typedef struct index
{
    int i;
    int j;
    int direction;
}idx;

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

int read_vector(int vec[], int size, int stop_value)
{
    if(size <= 0)
        return -1;
    int i = 0;
    while(size)
    {
        if(!scanf("%d", vec))
            return -2;
        if(*vec == stop_value)
            break;
        vec++;
        i++;
        size--;
    }
    if(!i)
        return -1;
    return i;
}

int main(void)
{
    printf("podaj liczby:\n");
    int **matrix = init_int_matrix(MATRIX_SIZE, MATRIX_SIZE);
    int output = read_int_matrix(matrix, MATRIX_SIZE, MATRIX_SIZE);
    if(output == -1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("podaj liczby:\n");
    int vec[VEC_SIZE];
    int vec_size = VEC_SIZE;
    if((vec_size = read_vector(vec, vec_size, 0)) == -1)
    {
        printf("not enough data available");
        return 2;
    }
    if(vec_size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    idx indexes[MATRIX_SIZE * MATRIX_SIZE * 2];
    int idx_count = 0;
    for(int i = 0; i < MATRIX_SIZE; i++)
        for(int j = 0; j < MATRIX_SIZE; j++)
        {
            if(j < (MATRIX_SIZE - vec_size) + 1)
            {
                for(int k = 0; k < vec_size; k++)
                {
                    if(vec[k] != matrix[i][j + k])
                        break;
                    if(k == vec_size - 1)
                    {
                        indexes[idx_count].direction = 2;
                        indexes[idx_count].i = i;
                        indexes[idx_count++].j = j;
                    }
                }
            }
            if(i < (MATRIX_SIZE - vec_size) + 1)
            {
                for(int k = 0; k < vec_size; k++)
                {
                    if(vec[k] != matrix[i + k][j])
                        break;
                    if(k == vec_size - 1)
                    {
                        indexes[idx_count].direction = 1;
                        indexes[idx_count].i = i;
                        indexes[idx_count++].j = j;
                    }
                }
            }
        }
    printf("%d\n", idx_count);
    for(int i = 0; i < idx_count; i++)
        printf("%d %d %d\n", indexes[i].direction, indexes[i].j, indexes[i].i);
    return 0;
}