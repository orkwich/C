#include <stdio.h>
#include <string.h>

struct student_t {
    char name[20];
    char surname[40];
    int index;
};

struct student_t* read(struct student_t* p, int *err_code)
{
    if(p == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
    }
    if(scanf("%20[,A-Za-z] ", p->name) != 1 || strchr(p->name, ',') == NULL)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    strtok(p->name, ",");

    if(scanf("%39[ A-Za-z], ", p->surname) != 1)

    int i = 0;
    char c = '\0';
    while((c = getchar()) != '\0' && c != '\n' && i < 40)
    {
        if(c != ',')
            *(p->surname + i++) = c;
        else
        {
            *(p->surname + i) = '\0';
            i = -1;
            break;
        }
    }
    if(i != -1)
    {
        if(err_code != NULL)
            *err_code = 2;
        return NULL;
    }
    if(scanf("%d", &(p->index)) != 1)
    {
        if(err_code != NULL)
            *err_code = 3;
        return NULL;
    }
    if(err_code != NULL)
        *err_code = 0;
    return p;
}

void show(const struct student_t* p)
{
    if(p == NULL)
        return;
    printf("%s %s, %d", p->name, p->surname, p->index);
}

int main(void)
{
    printf("Podaj dane:\n");
    int err_code = -1;
    struct student_t p;
    if(read(&p, &err_code) == NULL)
    {
        printf("Incorrect input");
        return err_code;
    }
    show(&p);
    return 0;
}