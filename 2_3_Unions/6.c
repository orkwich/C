#include <stdio.h>
#include <stdlib.h>
#define INPUT_SIZE 8 * 5
#define FNAME_MAX_SIZE 50

union bit_set
{
    unsigned char byte;
    struct
    {
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
        unsigned char bit8 : 1;
    } bits;
};

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    union bit_set *bmp = malloc(sizeof(union bit_set) * INPUT_SIZE);
    if(bmp == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    char *fname = malloc(sizeof(char) * (FNAME_MAX_SIZE + 1));
    if(fname == NULL)
    {
        free(bmp);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter values: ");
    int n = 0;
    while(scanf("%hhx", &((bmp + n++)->byte)) == 1 && n < INPUT_SIZE);
    if(n != INPUT_SIZE)
    {
        free(bmp);
        free(fname);
        printf("Incorrect input");
        return 1;
    }
    clear();
    printf("Podaj nazwe pliku: ");
    if(scanf("%50s", fname) != 1)
    {
        free(bmp);
        free(fname);
        printf("Incorrect input");
        return 1;
    }
    FILE *f = fopen(fname, "w");
    for(int i = 0; i < 40; i++)
    {
        if((bmp + i)->bits.bit8)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit7)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit6)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit5)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit4)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit3)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit2)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((bmp + i)->bits.bit1)
        {
            printf("#");
            if(f != NULL)
                fprintf(f, "#");
        }
        else
        {
            printf(" ");
            if(f != NULL)
                fprintf(f, " ");
        }
        if((i + 1) % 5 == 0)
        {
            printf("\n");
            if(f != NULL)
                fprintf(f, "\n");
        }
    }
    if(f == NULL)
    {
        free(bmp);
        free(fname);
        printf("Couldn't create file");
        return 5;
    }
    fclose(f);
    printf("File saved");
    free(bmp);
    free(fname);
    return 0;
}