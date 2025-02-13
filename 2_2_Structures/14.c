#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 100

struct student_t {
    char name[20];
    char surname[40];
    int index;
};

void show(const struct student_t* p)
{
    if(p == NULL)
        return;
    printf("%s %s\n", p->name, p->surname);
}

int fcount_lines(FILE *f)
{
    int i = 0;
    char c = '\0';
    fseek(f, 0, SEEK_SET);
    while((c = getc(f)) != EOF)
        if(c == '\n')
            i++;
    return i;
}

void fset_line(FILE *f, int line)
{
    fseek(f, 0, SEEK_SET);
    if(line == 0)
        return;
    int i = 0;
    char c = '\0';
    while((c = getc(f)) != EOF)
        if(c == '\n')
            if(++i == line)
                return;
    fseek(f, -1, SEEK_END);
}

void format_surname(struct student_t *student)
{
    if(*(student->name + strlen(student->name) - 1) == 'a')
        if(*(student->surname + strlen(student->surname) - 1) == 'i' && *(student->surname + strlen(student->surname) - 2) == 'k')
            *(student->surname + strlen(student->surname) - 1) = 'a';
}

void students_generate(struct student_t *tab, FILE *f_names, FILE *f_surnames, int size)
{
    if(tab == NULL || f_names == NULL || f_surnames == NULL)
        return;
    srand(time(NULL));
    int names_count = fcount_lines(f_names);
    int surnames_count = fcount_lines(f_surnames);
    for(int i = 0; i < size; i++)
    {
        int name_line = rand() % (names_count + 1);
        int surname_line = rand() % (surnames_count + 1);
        fset_line(f_names, name_line);
        fset_line(f_surnames, surname_line);
        fscanf(f_names, "%s", (tab + i)->name);
        fscanf(f_surnames, "%s", (tab + i)->surname);
        format_surname(tab + i);
    }
}

int main(void)
{
    FILE *f_names = fopen("imiona.txt", "r");
    FILE *f_surnames = fopen("nazwiska.txt", "r");
    if(f_names == NULL && f_surnames != NULL)
    {
        fclose(f_surnames);
        printf("Couldn't open file");
        return 4;
    }
    if(f_names != NULL && f_surnames == NULL)
    {
        fclose(f_names);
        printf("Couldn't open file");
        return 4;
    }
    if(f_names == NULL && f_surnames == NULL)
    {
        printf("Couldn't open file");
        return 4;
    }
    printf("Enter a number of students to generate: ");
    int n = 0;
    if(scanf("%3d", &n) != 1 || n <= 0 || n > 100)
    {
        fclose(f_names);
        fclose(f_surnames);
        printf("Error");
        return 1;
    }
    struct student_t tab[SIZE];
    students_generate(tab, f_names, f_surnames, n);
    for(int i = 0; i < n; i++)
        show(tab + i);
    fclose(f_names);
    fclose(f_surnames);
    return 0;
}