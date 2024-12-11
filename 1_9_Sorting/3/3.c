#include "sort.h"

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    printf("Podaj wektor:\n");
    int vec[SIZE];
    int size = SIZE;
    size = read_vector(vec, size, 0);
    if(size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    clear();
    printf("Podaj kierunek sortowania: ");
    int dir = 0;
    if(scanf("%d", &dir) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(dir != 1 && dir != 2)
    {
        printf("Incorrect input data");
        return 2;
    }
    selection_sort(vec, size, dir);
    display_vector(vec, size);
    return 0;
}