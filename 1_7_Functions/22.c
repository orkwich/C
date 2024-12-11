#include <stdio.h>

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

void display_vector(const int vec[], int size)
{
    if(size <= 0)
        return;
    for(int i = 0; i < size; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

int concat_begin(const int first[], int size, const int second[], int size2, int dest[], int size3)
{
    if(size <= 0 || size2 <= 0 || size3 <= 0)
        return -1;
    if(size + size2 > size3)
        return -2;
    int i = 0;
    for(;i < size; i++)
        dest[i] = first[i];
    for(int j = 0; j < size2; i++, j++)
        dest[i] = second[j];
    return i;
}
int concat_end(const int first[], int size, const int second[], int size2, int dest[], int size3)
{
    if(size <= 0 || size2 <= 0 || size3 <= 0)
        return -1;
    if(size + size2 > size3)
        return -2;
    int i = 0;
    for(;i < size2; i++)
        dest[i] = second[i];
    for(int j = 0; j < size; i++, j++)
        dest[i] = first[j];
    return i;
}
int concat_zip(const int first[], int size, const int second[], int size2, int dest[], int size3)
{
    if(size <= 0 || size2 <= 0 || size3 <= 0)
        return -1;
    if(size + size2 > size3)
        return -2;
    int i;
    int j;
    if(size >= size2)
        j = size2 * 2;
    else
        j = size * 2;
    for(i = 0; i < j; i++)
        if(i % 2)
            dest[i] = second[i / 2];
        else
            dest[i] = first[i / 2];
    if(i == size * 2)
        for(j = i / 2; j < size2; j++, i++)
            dest[i] = second[j];
    else
        for(j = i / 2; j < size; j++, i++)
            dest[i] = first[j];
    return i;
}

void clear()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    int vec1[50];
    int vec2[50];
    int size1 = 50;
    int size2 = 50;
    printf("Podaj pierwszy wektor: ");
    size1 = read_vector(vec1, size1, 0);
    if(size1 == -1)
    {
        printf("Not enough data available");
        return 2;
    }
    if(size1 == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    clear();
    printf("Podaj drugi wektror: ");
    size2 = read_vector(vec2, size2, 0);
    if(size2 == -1)
    {
        printf("Not enough data available");
        return 2;
    }
    if(size2 == -2)
    {
        printf("Incorrect input");
        return 1;
    }
    clear();
    display_vector(vec1, size1);
    display_vector(vec2, size2);
    int vec3[50];
    int size3 = 50;
    if(size1 + size2 > size3)
        printf("Output buffer is too small");
    else
    {
        size3 = concat_begin(vec1, size1, vec2, size2, vec3, size3);
        if(size3 > 0)
            display_vector(vec3, size3);

        size3 = concat_end(vec1, size1, vec2, size2, vec3, size3);
        if(size3 > 0)
            display_vector(vec3, size3);
    
        size3 = concat_zip(vec1, size1, vec2, size2, vec3, size3);
        if(size3 > 0)
            display_vector(vec3, size3);
    }
    return 0;
}