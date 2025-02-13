#include <stdio.h>

int main(void)
{
    FILE *f2 = fopen("2.txt", "w");
    if(f2 == NULL)
    {
        printf("Couldn't create file");
        return 5;
    }
    FILE *f3 = fopen("3.txt", "w");
    if(f3 == NULL)
    {
        fclose(f2);
        printf("Couldn't create file");
        return 5;
    }
    FILE *f5 = fopen("5.txt", "w");
    if(f5 == NULL)
    {
        fclose(f2);
        fclose(f3);
        printf("Couldn't create file");
        return 5;
    }
    FILE *f0 = fopen("0.txt", "w");
    if(f0 == NULL)
    {
        fclose(f2);
        fclose(f3);
        fclose(f5);
        printf("Couldn't create file");
        return 5;
    }
    printf("Podaj liczby:\n");
    int number = 1;
    while(scanf("%d", &number) && number)
    {
        int flag = 1;
        if(number % 2 == 0)
        {
            flag = 0;
            fprintf(f2, "%d\n", number);
        }
        if(number % 3 == 0)
        {
            flag = 0;
            fprintf(f3, "%d\n", number);
        }
        if(number % 5 == 0)
        {
            flag = 0;
            fprintf(f5, "%d\n", number);
        }
        if(flag)
            fprintf(f0, "%d\n", number);
    }
    fclose(f2);
    fclose(f3);
    fclose(f5);
    fclose(f0);
    printf("Files saved");
    return 0;
}