#include <stdio.h>
#define WIDTH 5
#define HEIGHT 5

int abs(int x)
{
    if(x < 0)
        return -x;
    return x;
}

int dd_test(const int *ptr, int width, int height)
{
    if(ptr == NULL || width <= 0 || height <= 0 || width != height)
        return -1;
    for(int i = 0; i < height; i++)
    {
        int sum = 0;
        for(int j = 0; j < width; j++)
            if(i != j)
                sum += abs(*(ptr + j + (i * height)));
        if(sum >= abs(*(ptr + i + (i * height))))
            return 0;
    }
    return 1;
}

int main(void)
{
    printf("Podaj liczby:\n");
    int tab[HEIGHT][WIDTH];
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            if(scanf("%d", *(tab + i) + j) != 1)
            {
                printf("Incorrect input");
                return 1;
            }
    if(dd_test((int*)tab, WIDTH, HEIGHT))
        printf("YES");
    else
        printf("NO");
    return 0;
}