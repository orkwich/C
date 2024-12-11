#include "vector_utils.h"
#include "quicksort.h"

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    printf("Podaj wektor: ");
    int tab[MAX_SIZE];
    int size = MAX_SIZE;
    size = read_vector(tab, size, STOP);
    if(size == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size == -1)
    {
        printf("Not enough data available");
        return 3;
    }
    clear();
    printf("Podaj kierunek sortowania: ");
    int dir = 0;
    if(scanf("%d", &dir) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(dir != ASCENDING && dir != DESCENDING)
    {
        printf("Incorrect input data");
        return 2;
    }
    quicksort(tab, size, dir);
    display_vector(tab, size);
    return 0;
}