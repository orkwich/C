#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 50

enum figure_types
{
  TRIANGLE = 1,
  RECTANGLE,
  CIRCLE
};

struct point_t
{
  int x;
  int y;
};

struct rectangle_t
{
  struct point_t p;
  int width;
  int height;
};

struct circle_t
{
  struct point_t c;
  float r;
};

struct triangle_t
{
  struct point_t p1;
  struct point_t p2;
  struct point_t p3;
};

struct figure_t
{
  union
  {
    struct rectangle_t rect;
    struct triangle_t triangle;
    struct circle_t circ;
  };
  enum figure_types type;
};

float points_distance(struct point_t *p1, struct point_t *p2)
{
    return (float)sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

int validate_triangle(struct triangle_t *tri)
{
    if(tri->p1.x == tri->p2.x && tri->p1.y == tri->p2.y)
        return 1;
    if(tri->p1.x == tri->p3.x && tri->p1.y == tri->p3.y)
        return 1;
    if(tri->p3.x == tri->p2.x && tri->p3.y == tri->p2.y)
        return 1;
    float a = points_distance(&(tri->p1), &(tri->p2));
    float b = points_distance(&(tri->p2), &(tri->p3));
    float c = points_distance(&(tri->p3), &(tri->p1));
    int max = a;
    if(b > max)
        max = b;
    if(c > max)
        max = c;
    if(max >= a + b)
        return 1;
    if(max >= b + c)
        return 1;
    if(max >= c + a)
        return 1;
    return 0;
}

int validate_rectangle(struct rectangle_t *rec)
{
    if(rec->height <= 0 || rec->width <= 0)
        return 1;
    return 0;
}

int validate_circle(struct circle_t *circ)
{
    if(circ->r <= 0)
        return 1;
    return 0;
}

int validate_figure(struct figure_t *f)
{
    if(f->type == TRIANGLE)
        return validate_triangle(&(f->triangle));
    if(f->type == RECTANGLE)
        return validate_rectangle(&(f->rect));
    if(f->type == CIRCLE)
        return validate_circle(&(f->circ));
    return 1;
}

float area_triangle(const struct triangle_t *t)
{
    if(t == NULL)
        return -1;
    if(validate_triangle((struct triangle_t*)t))
        return -1;
    struct triangle_t *tmp = (struct triangle_t *)t;
    float a = points_distance(&(tmp->p1), &(tmp->p2));
    float b = points_distance(&(tmp->p2), &(tmp->p3));
    float c = points_distance(&(tmp->p3), &(tmp->p1));
    float p = (a + b + c) / 2;
    return (float)sqrt(p * (p - a) * (p - b) * (p - c));
}

float area_rectangle(const struct rectangle_t *r)
{
    if(r == NULL)
        return -1;
    if(validate_rectangle((struct rectangle_t*)r))
        return -1;
    return (float) r->height * r->width;
}

float area_circle(const struct circle_t *c)
{
    if(c == NULL)
        return -1;
    if(validate_circle((struct circle_t*)c))
        return -1;
    return (float) M_PI * pow(c->r, 2);
}

float area_figure(const struct figure_t *f)
{
    if(f == NULL)
        return -1;
    if(f->type == TRIANGLE)
        return area_triangle(&(f->triangle));
    if(f->type == CIRCLE)
        return area_circle(&(f->circ));
    if(f->type == RECTANGLE)
        return area_rectangle(&(f->rect));
    return -1;
}

void display_rectangle(const struct rectangle_t *rect)
{
    if(rect == NULL)
        return;
    printf("Rectangle (%d, %d), width = %d, height = %d\n", rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t)
{
    if(t == NULL)
        return;
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ)
{
    if(circ == NULL)
        return;
    printf("Circle (%d, %d), radius = %.6f\n", circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f)
{
    if(f == NULL)
        return;
    if(f->type == TRIANGLE)
        display_triangle(&(f->triangle));
    else if(f->type == CIRCLE)
        display_circle(&(f->circ));
    else if(f->type == RECTANGLE)
        display_rectangle(&(f->rect));
}

int cmp_areas(struct figure_t *f1, struct figure_t *f2)
{
    float area1 = area_figure(f1);
    float area2 = area_figure(f2);
    return -(area1 < area2) + (area1 > area2);
}

void swap_figure(int i, int j, struct figure_t **figures)
{
    if(i != j)
    {
        struct figure_t *tmp_f = *(figures + i);
        *(figures + i) = *(figures + j);
        *(figures + j) = tmp_f;
    }
}

int divide(int l, int r, struct figure_t **figures)
{
    int pivot = (l + r) / 2;
    int position = l;
    swap_figure(pivot, r, figures);
    for(int i = l; i < r; i++)
        if(cmp_areas(*(figures + r), *(figures + i)) < 0)
            swap_figure(position++, i, figures);
    swap_figure(position, r, figures);
    return position;
}

int quicksort_figures(int l, int r, struct figure_t **figures, int size)
{
    if(r < 0)
        r = -r;
    if(r >= size || l < 0)
        return 1;
    if(r > l)
    {
        int pivot = divide(l, r, figures);
        quicksort_figures(l, pivot, figures, size);
        quicksort_figures(pivot + 1, r, figures, size);
    }
    return 0;
}

int sort_by_area(struct figure_t **figures, int size)
{
    if(figures == NULL || size <= 0)
        return 1;
    for(int i = 0; i < size; i++)
        if(validate_figure(*(figures + i)))
            return 1;
    return quicksort_figures(0, size - 1, figures, size);
}

int validate_type(enum figure_types type)
{
    if(type < 4 && type >= 0)
        return 1;
    return 0;
}

int input_triangle(struct triangle_t *tri)
{
    printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
    if(scanf("%d", &(tri->p1.x)) != 1)
        return 1;
    if(scanf("%d", &(tri->p1.y)) != 1)
        return 1;
    if(scanf("%d", &(tri->p2.x)) != 1)
        return 1;
    if(scanf("%d", &(tri->p2.y)) != 1)
        return 1;
    if(scanf("%d", &(tri->p3.x)) != 1)
        return 1;
    if(scanf("%d", &(tri->p3.y)) != 1)
        return 1;
    return 0;
}

int input_rectangle(struct rectangle_t *rec)
{
    printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
    if(scanf("%d", &(rec->p.x)) != 1)
        return 1;
    if(scanf("%d", &(rec->p.y)) != 1)
        return 1;
    if(scanf("%d", &(rec->width)) != 1)
        return 1;
    if(scanf("%d", &(rec->height)) != 1)
        return 1;
    return 0;
}

int input_circle(struct circle_t *circ)
{
    printf("Enter coordinates and radius of a circle: ");
    if(scanf("%d", &(circ->c.x)) != 1)
        return 1;
    if(scanf("%d", &(circ->c.y)) != 1)
        return 1;
    if(scanf("%f", &(circ->r)) != 1)
        return 1;
    return 0;
}

int input_figure(struct figure_t *f, enum figure_types type)
{
    if(type == TRIANGLE)
    {
        f->type = type;
        return input_triangle(&(f->triangle));
    }
    if(type == RECTANGLE)
    {
        f->type = type;
        return input_rectangle(&(f->rect));
    }
    if(type == CIRCLE)
    {
        f->type = type;
        return input_circle(&(f->circ));
    }
    return 1;
}

int main(void)
{
    enum figure_types type = 1;
    int size = 0;
    struct figure_t *figures = malloc(sizeof(struct figure_t) * SIZE);
    while(size < SIZE)
    {
        printf("Enter figure's type: ");
        int tmp;
        if(scanf("%d", &tmp) != 1)
        {
            free(figures);
            printf("Incorrect input");
            return 1;
        }
        if(tmp == 0)
            break;
        type = tmp;
        if(validate_type(type) == 0)
        {
            free(figures);
            printf("Incorrect input data");
            return 2;
        }
        if(input_figure(figures + size++, type) == 1)
        {
            free(figures);
            printf("Incorrect input");
            return 1;
        }
    }
    for(int i = 0; i < size; i++)
        if(validate_figure(figures + i))
        {
            free(figures);
            printf("Incorrect input data");
            return 2;
        }
    struct figure_t **tmp_fig = malloc(sizeof(struct figure_t *) * size);
    for(int i = 0; i < size; i++)
        *(tmp_fig + i) = figures + i;
    sort_by_area(tmp_fig, size);
    for(int i = 0; i < size; i++)
        display_figure(*(tmp_fig + i));
    free(tmp_fig);
    free(figures);
    return 0;
}