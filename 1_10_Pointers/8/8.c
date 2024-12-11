#include "vector_utils.h"
#define SIZE 100
#define STOP -1

int sort(int* tab, int size)
{
    if(size <= 0 || tab == NULL)
        return 1;
    for(int i = size - 1; i >= 0; i--)
    {
        int is_sorted = 1;
        for(int j = 1; j <= i; j++)
        {
            if(*(tab + (j - 1)) > *(tab + j))
            {
                is_sorted = 0;
                int tmp = *(tab + (j - 1));
                *(tab + (j - 1)) = *(tab + j);
                *(tab + j) = tmp;
            }
        }
        if(is_sorted)
            return 0;
    }
    return 0;
}

int main(void)
{
    printf("Wpisuj wartosci calkowite\n");
    int vec[SIZE];
    int size = SIZE;
    size = read_vector(vec, size, STOP);
    if(size == 0 || size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    sort(vec, size);
    display_vector(vec, size);
    return 0;
}