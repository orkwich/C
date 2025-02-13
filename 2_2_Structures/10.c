#include <stdio.h>
#define MAX_POINT_COUNT 100
#define STR_SIZE 30

struct point_t
{
    int x;
    int y;
};

int save_points_b(const char *filename, const struct point_t* p, unsigned int N)
{
    if(filename == NULL || p == NULL || N == 0)
        return 1;
    FILE *f = fopen(filename, "wb");
    if(f == NULL)
        return 2;
    if(fwrite(p, sizeof(struct point_t), N, f) != N)
    {
        fclose(f);
        return 3;
    }
    fclose(f);
    return 0;
}

struct point_t* read(struct point_t* p)
{
    if(scanf("%d %d", &(p->x), &(p->y)) != 2)
        return NULL;
    return p;
}

int main(void)
{
    printf("Podaj liczbe punktow: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    if(n > 100)
        n = 100;
    printf("Podaj punkty:\n");
    struct point_t p[MAX_POINT_COUNT];
    for(int i = 0; i < n; i++)
        if(read(p + i) == NULL)
        {
            printf("Incorrect input");
            return 1;
        }
    printf("Podaj plik:\n");
    char filename[STR_SIZE + 1];
    scanf("%30s", filename);
    if(save_points_b(filename, p, (unsigned int)n) == 2)    
    {
        printf("Couldn't create file");
        return 5;
    }
    printf("File saved");
    return 0;
}