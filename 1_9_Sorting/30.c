#include <stdio.h>
#include <stdlib.h>

int is_number(char string[])
{
    while(*string != '\0')
    {
        if(*string == '\n')
            return 0;
        int dif = '9' - *string++;
        if(dif < 0 || dif > '9')
            return 0;
    }
    return 1;
}

int cout_front_zeros(char string[])
{
    int i = 0;
    while(*string++ == '0')
        i++;
    return i;
}

void delete_front_zeros(char string[])
{
    int i = cout_front_zeros(string);
    if(!i)
        return;
    do
        *string = *(string + i);
    while(*(string++ + i) != '\0');
}

void swap(int i, int j, char tab[])
{
    if(i != j)
    {
        char tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
}

int divide_asc(int l, int r, char tab[])
{
    int pivot = (l + r) / 2;
    int position = l;
    swap(pivot, r, tab);
    for(int i = l; i < r; i++)
        if(tab[r] > tab[i])
            swap(position++, i, tab);
    swap(position, r, tab);
    return position;
}

int quicksort_asc(int l, int r, char tab[], int tabSize)
{
    if(r < 0)
        r = -r;
    if(r >= tabSize || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide_asc(l, r, tab);
        quicksort_asc(l, pivot, tab, tabSize);
        quicksort_asc(pivot + 1, r, tab, tabSize);
    }
    return 0;
}

int string_length(char* string)
{
    int i = 0;
    while(*string++)
        i++;
    return i;
}

int sort_digits(char tab[])
{
    if(!is_number(tab))
        return 1;
    int size = string_length(tab);
    int out = quicksort_asc(0, size - 1, tab, size);
    delete_front_zeros(tab);
    return out;
}

int main(void)
{
    printf("Podaj liczbe:\n");
    char* string = malloc(sizeof(char) * 501);
    if(scanf("%500s", string) != 1 || sort_digits(string) != 0)
    {
        printf("Incorrect input data");
        free(string);
        return 2;
    }
    if(*string == '\0')
    {
        printf("nothing to show");
        free(string);
        return 0;
    }
    printf("%s\n", string);
    free(string);
    return 0;
}