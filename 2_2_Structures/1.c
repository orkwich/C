#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct point_t {
    int x;
    int y;
};

struct point_t* set(struct point_t* p, int x, int y)
{
    if(p == NULL)
        return NULL;
    p->x = x;
    p->y = y;
    return p;
}

void show(const struct point_t* p)
{
    if(p == NULL)
        return;
    printf("x = %d; y = %d\n", p->x, p->y);
}

struct point_t* read(struct point_t* p)
{
    if(p == NULL)
        return NULL;
    printf("Podaj wspolrzedna x: ");
    if(scanf("%d", &(p->x)) != 1)
        return NULL;
    printf("Podaj wspolrzedna y: ");
    if(scanf("%d", &(p->y)) != 1)
        return NULL;
    return p;
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code)
{
    if(p1 == NULL || p2 == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return -1;
    }
    if(err_code != NULL)
        *err_code = 0;
    return (float)sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

struct point_t* set_random(struct point_t* p)
{
    srand(time(NULL));
    return set(p, (rand() % 21) - 10, (rand() % 21) - 10);
}

int main(void)
{
    struct point_t* p1 = malloc(sizeof(struct point_t));
    if(read(p1) == NULL)
    {
        printf("Incorrect input");
        free(p1);
        return 1;
    }
    struct point_t* p2 = malloc(sizeof(struct point_t));
    p2 = set_random(p2);
    show(p1);
    show(p2);
    float dist = distance(p1, p2, NULL);
    printf("%.2f", dist);
    free(p1);
    free(p2);
    return 0;
}