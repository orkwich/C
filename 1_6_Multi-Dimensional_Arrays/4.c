#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BUFF_SIZE 50
#define SIZE 4

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
    srand(time(NULL));
    int **matrixA = init_int_matrix(SIZE, SIZE);
    int **matrixB = init_int_matrix(SIZE, SIZE);
    int **matrixC = init_int_matrix(SIZE, SIZE);
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
            matrixC[i][j] = 0;
        }
        matrixC[i][i] = 1;
    }
    display_int_matrix(matrixA, SIZE, SIZE);
    printf("\n");
    display_int_matrix(matrixB, SIZE, SIZE);
    printf("\n");
    display_int_matrix(matrixC, SIZE, SIZE);
    return 0;
}