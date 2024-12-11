#include <stdio.h>
#define SIZE 30

int is_lowercase_letter(char c)
{
    int dif = 'z' - c;
    if(dif < 0 || dif > ('z' - 'a'))
        return 0;
    return 1;
}

int are_lowercase_letters(char string[])
{
    while(*string != '\0')
        if(!is_lowercase_letter(*string++))
            return 0;
    return 1;
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

int sort_lowercase(char tab[])
{
    if(!are_lowercase_letters(tab) || *tab == '\0')
        return 1;
    int length = string_length(tab);
    return quicksort_asc(0, length - 1, tab, length);
}

int main(void)
{
    printf("Wprowadz tekst do posortowania (tylko male litery):\n");
    char string[SIZE + 1];
    if(scanf("%30s", string) != 1 || sort_lowercase(string))
    {
        printf("Incorrect input data");
        return 2;
    }
    printf("%s\n", string);
    return 0;
}