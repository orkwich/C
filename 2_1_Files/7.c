#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_RAND 1000

int main(void)
{
    srand(time(NULL));
    printf("Podaj liczbe liczb:\n");
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(number <= 0 || number > 1000)
    {
        printf("Incorrect input data");
        return 2;
    }
    char fname[10];
    int fcount = 0;
    sprintf(fname, "%d.txt", fcount++);
    FILE *f = fopen(fname, "w");
    if(f == NULL)
    {
        printf("Couldn't create file");
        return 5;
    }
    printf("%s\n", fname);
    for(int i = 0; i < number; i++)
    {
        if(i % 10 == 0 && i)
        {
            fclose(f);
            sprintf(fname, "%d.txt", fcount++);            
            f = fopen(fname, "w");
            if(f == NULL)
            {
                printf("Couldn't create file");
                return 5;
            }
            printf("%s\n", fname);
        }
        fprintf(f, "%d\n", rand() % (MAX_RAND + 1));
    }
    fclose(f);
}