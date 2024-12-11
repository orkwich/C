#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BUFF_SIZE 50
#define SIZE 10

typedef struct point
{
    int i;
    int j;
    int value;
}point;


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

point minimum(int **matrix, int rows, int columns)
{
    point min;
    min.value = matrix[0][0];
    min.i = 0;
    min.j = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(matrix[i][j] < min.value)
            {
                min.value = matrix[i][j];
                min.i = i;
                min.j = j;
            }
    return min;
}

point maximum(int **matrix, int rows, int columns)
{
    point max;
    max.value = matrix[0][0];
    max.i = 0;
    max.j = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(matrix[i][j] > max.value)
            {
                max.value = matrix[i][j];
                max.i = i;
                max.j = j;
            }
    return max;
}

int count(int **matrix, int rows, int columns, int value)
{
    int count = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(matrix[i][j] == value)
                count++;
    return count;
}

int sum_matrix(int **matrix, int rows, int columns)
{
    int sum = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            sum += matrix[i][j];
    return sum;
}

point closest_value(int **matrix, int rows, int columns, float value)
{
    point result;
    result.value = matrix[0][0];
    result.i = 0;
    result.j = 0;
    float diff = value - result.value;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        if(abs(diff) > abs(value - matrix[i][j]))
        {
            diff = value - matrix[i][j];
            result.value = matrix[i][j];
            result.i = i;
            result.j = j;
        }
    return result;
}

float side_length(point point1, point point2)
{
    return sqrt((pow(point1.i - point2.i,2) + pow(point1.j - point2.j, 2)));
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
    point min = minimum(matrix, SIZE, SIZE);
    point max = maximum(matrix, SIZE, SIZE);
    int sum = sum_matrix(matrix, SIZE, SIZE);
    float avg = (float) sum / (SIZE * SIZE);
    point closest_to_avg = closest_value(matrix, SIZE, SIZE, avg);
    if(count(matrix, SIZE, SIZE, min.value) > 1 || count(matrix, SIZE, SIZE, max.value) > 1 || count(matrix, SIZE, SIZE, closest_to_avg.value) > 1)
    {
        printf("error");
        return 2;
    }
    float side_a = side_length(min, max);
    float side_b = side_length(max, closest_to_avg);
    float side_c = side_length(closest_to_avg, min);
    printf("%.2f %.2f %.2f", side_a, side_b, side_c);
    return 0;
}