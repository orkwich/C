#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct point_t
{
    int x;
    int y;
};

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

struct point_t* set(struct point_t* p, int x, int y)
{
    if(p == NULL)
        return NULL;
    p->x = x;
    p->y = y;
    return p;
}

struct point_t* set_random(struct point_t* p)
{
    srand(time(NULL));
    return set(p, (rand() % 21) - 10, (rand() % 21) - 10);
}

void show(const struct point_t* p)
{
    if(p == NULL)
        return;
    printf("x = %d; y = %d\n", p->x, p->y);
}

int save_point_b(const char *filename, const struct point_t* p)
{
    if(filename == NULL || p == NULL)
        return 1;
    FILE *f = fopen(filename, "wb");
    if(f == NULL)
        return 2;
    if(fwrite(p, sizeof(struct point_t), 1, f) != 1)
    {
        fclose(f);
        return 3;
    }
    fclose(f);
    return 0;
}

int load_point_b(const char *filename, struct point_t* p)
{
    if(filename == NULL || p == NULL)
        return 1;
    FILE *f = fopen(filename, "rb");
    if(f == NULL)
        return 2;
    if(fread(p, sizeof(struct point_t), 1, f) != 1)
    {
        fclose(f);
        return 3;
    }
    fclose(f);
    return 0;
}

int save_point_t(const char *filename, const struct point_t* p)
{
    if(filename == NULL || p == NULL)
        return 1;
    FILE *f = fopen(filename, "w");
    if(f == NULL)
        return 2;
    if(fprintf(f, "%d %d", p->x, p->y) < 0)
    {
        fclose(f);
        return 3;
    }
    fclose(f);
    return 0;
}

int load_point_t(const char *filename, struct point_t* p)
{
    if(filename == NULL || p == NULL)
        return 1;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 2;
    if(fscanf(f, "%d %d", &(p->x), &(p->y)) != 2)
    {
        fclose(f);
        return 3;
    }
    fclose(f);
    return 0;
}

int check_format(char *filename)
{
    int len = strlen(filename);
    if(strcmp(filename + len - 4, ".txt") == 0)
        return 0;
    if(strcmp(filename + len - 4, ".bin") == 0)
        return 0;
    return 1;
}

int save(char *filename, struct point_t *p)
{
    if(filename == NULL || p == NULL)
        return 1;
    if(check_format(filename))
        return -1;
    if(strstr(filename, ".txt") != NULL)
        return save_point_t(filename, p);
    if(strstr(filename, ".bin") != NULL)
        return save_point_b(filename, p);
    return -1;
}

int load(char *filename, struct point_t *p)
{
    if(filename == NULL || p == NULL)
        return 1;
    if(strstr(filename, ".txt") != NULL)
        return load_point_t(filename, p);
    if(strstr(filename, ".bin") != NULL)
        return load_point_b(filename, p);
    return -1;
}

int main(void)
{
    struct point_t p;
    set_random(&p);
    show(&p);
    printf("Podaj sciezke do pliku:\n");
    char filename[31];
    scanf("%30s", filename);
    int err_code = save(filename, &p);
    if(err_code == -1)
    {
        printf("Unsupported file format");
        return 7;
    }
    if(err_code != 0)
    {
        printf("Couldn't create file");
        return 5;
    }
    printf("File saved\n");
    clear();
    printf("Do you want to read the file (Y/N)? ");
    char c = '\0';
    scanf("%c", &c);
    if(c != 'y' && c != 'n' && c != 'Y' && c != 'N')
    {
        printf("Incorrect input");
        return 1;
    }
    if(c == 'y' || c == 'Y')
    {
        err_code = load(filename, &p);
        if(err_code == 2)
        {
            printf("Couldn't open file");
            return 4;
        }
        if(err_code == 3)
        {
            printf("File corrupted");
            return 6;
        }
        show(&p);
    }
    return 0;
}