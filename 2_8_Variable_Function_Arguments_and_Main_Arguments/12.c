#include <stdio.h>
#include <ctype.h>

int is_int(char *str)
{
    if(*str == '-')
        str++;
    while(*str != '\0')
        if(!isdigit(*str++))
            return 0;
    return 1;
}

int main(int args, char **argv)
{
    if(args < 2)
    {
        printf("Not enough arguments");
        return 9;
    }
    int sum = 0;
    for(int i = 1; i < args; i++)
    {
        if(!is_int(*(argv + i)))
        {
            printf("Incorrect input");
            return 1;
        }
        int tmp;
        sscanf(*(argv + i), "%d", &tmp);
        sum += tmp;
    }
    printf("%d", sum);
    return 0;
}