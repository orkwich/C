#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME_SIZE 30

struct point_t
{
    int x;
    int y;
};

struct point_t* maze_find_a(char **maze)
{
    if(maze == NULL)
        return NULL;
    int j = 0;
    while(*(maze + j) != NULL)
    {
        int i = 0;
        while(*(*(maze + j) + i) != '\0')
        {
            if(*(*(maze + j) + i) == 'a')
            {
                struct point_t *p = malloc(sizeof(struct point_t));
                p->x = i;
                p->y = j;
                return p;
            }
            i++;
        }
        j++;
    }
    return NULL;
}

int fcount_lines(FILE *f)
{
    if(f == NULL)
        return -1;
    char c;
    int i = 0;
    fseek(f, 0, SEEK_SET);
    if(feof(f))
        return 0;
    while((c = getc(f)) != EOF)
        if(c == '\n')
            i++;
    return i + 1;
}

int maze_count_lines(char **str)
{
    if(str == NULL)
        return -1;
    int i = 0;
    while(*(str + i) != NULL)
        i++;
    return i;
}

int fvalid(FILE *f)
{
    if(f == NULL)
        return 0;
    char c;
    int i = 0;
    int line_len = -1;
    fseek(f, 0, SEEK_SET);
    while((c = getc(f)) != EOF)
    {
        if(c != '#' && c != ' ' && c != 'a' && c != 'b' && c != '\n')
            return 0;
        if(c == '\n')
        {
            if(line_len == -1)
                line_len = i;
            if(i != line_len)
                return 0;
            i = 0;
        } else
            i++;
    }
    return line_len;
}

int is_a_and_b(char **maze)
{
    if(maze == NULL)
        return 0;
    int j = 0;
    int flag_a = 1;
    int flag_b = 1;
    while(*(maze + j) != NULL)
    {
        int i = 0;
        while(*(*(maze + j) + i) != '\0')
        {
            if(*(*(maze + j) + i) == 'a')
                if(!flag_a)
                    return 0;
                else
                    flag_a = 0;
            if(*(*(maze + j) + i) == 'b')
                if(!flag_b)
                    return 0;
                else
                    flag_b = 0;
            i++;
        }
        j++;
    }
    if(flag_a || flag_b)
        return 0;
    return 1;
}

int load_maze(const char *filename, char ***labirynth)
{
    if(filename == NULL || labirynth == NULL)
        return 1;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
    {
        *labirynth = NULL;
        return 2;
    }
    int line_len = fvalid(f);
    if(!line_len)
    {
        *labirynth = NULL;
        fclose(f);
        return 3;
    }
    int lines = fcount_lines(f);
    if(lines < 2)
    {
        *labirynth = NULL;
        fclose(f);
        return 3;
    }
    *labirynth = malloc(sizeof(char*) * (lines + 1));
    if(*labirynth == NULL)
    {
        *labirynth = NULL;
        fclose(f);
        return 4;
    }
    for(int i = 0; i < lines; i++)
    {
        *((*labirynth) + i) = malloc(sizeof(char) * (line_len + 1));
        if(*((*labirynth) + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*((*labirynth) + i));
            free(*labirynth);
            *labirynth = NULL;
            fclose(f);
            return 4;
        }
    }
    *((*labirynth) + lines) = NULL;
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < lines; i++)
        fscanf(f, "%[# ab]\n", *((*labirynth) + i));
    fclose(f);
    return 0;
}

void print_maze(char **maze)
{
    if(maze == NULL)
        return;
    int i = 0;
    while(*(maze + i) != NULL)
        printf("%s\n", *(maze + i++));
}

int solve_maze(char **maze, int x, int y)
{
    if(maze == NULL)
        return -1;
    int line_len = strlen(*maze);
    int line_count = maze_count_lines(maze);
    if(x < 1 || x > (line_len - 2) || y < 1 || y > (line_count - 2) || *(*(maze + y) + x) == '#')
        return -1;
    for(int i = 0; i < line_count; i++)
        if(strlen(*(maze + i)) != (size_t)line_len)
            return -1;
    if(*(*(maze + y) + x) == 'b')
        return 1;
    if(*(*(maze + y) + x + 1) == ' ' || *(*(maze + y) + x + 1) == 'b')
    {
        if(*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = '*';
        if(*(*(maze + y) + x + 1) == 'b')
            return 1;
        int res = solve_maze(maze, x + 1, y);
        if(res == 1)
            return 1;
        if(res == 0 && *(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = ' ';
    }
    if(*(*(maze + y) + x - 1) == ' ' || *(*(maze + y) + x - 1) == 'b')
    {
        if(*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = '*';
        if(*(*(maze + y) + x - 1) == 'b')
            return 1;
        int res = solve_maze(maze, x - 1, y);
        if(res == 1)
            return 1;
        if(res == 0 && *(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = ' ';
    }
    if(*(*(maze + y + 1) + x) == ' ' || *(*(maze + y + 1) + x) == 'b')
    {
        if(*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = '*';
        if(*(*(maze + y + 1) + x) == 'b')
            return 1;
        int res = solve_maze(maze, x, y + 1);
        if(res == 1)
            return 1;
        if(res == 0 && *(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = ' ';
    }
    if(*(*(maze + y - 1) + x) == ' ' || *(*(maze + y - 1) + x) == 'b')
    {
        if(*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = '*';
        if(*(*(maze + y - 1) + x) == 'b')
            return 1;
        int res = solve_maze(maze, x, y - 1);
        if(res == 1)
            return 1;
        if(res == 0 && *(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = ' ';
    }
    return 0;
}

void free_maze(char **maze)
{
    if(maze == NULL)
        return;
    int i = 0;
    while(*(maze + i) != NULL)
        free(*(maze + i++));
    free(maze);
}

int main(void)
{
    char *fname = malloc(sizeof(char) * (FNAME_SIZE + 1));
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter filename: ");
    scanf("%30s", fname);
    char **maze;
    int res = load_maze(fname, &maze);
    free(fname);
    if(res == 2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(res == 3)
    {
        printf("File corrupted");
        return 6;
    }
    if(res == 4)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    if(!is_a_and_b(maze))
    {
        printf("File corrupted");
        free_maze(maze);
        return 6;
    }
    struct point_t *a = maze_find_a(maze);
    res = solve_maze(maze, a->x, a->y);
    if(res == 0)
        printf("Couldn't find path");
    else
        print_maze(maze);
    free_maze(maze);
    free(a);
    return 0;
}