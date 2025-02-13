#include "vector.h"

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    printf("Podaj pojemnosc tablicy: ");
    int n = 0;
    if(scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct vector_t *v;
    if(vector_create_struct(&v, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    int input = -1;
    while(input != 0)
    {
        printf("Co chcesz zrobic: ");
        if(scanf("%d", &input) != 1)
        {
            printf("Incorrect input");
            vector_destroy_struct(&v);
            return 1;
        }
        clear();
        if(input == 1)
        {
            printf("Podaj kolejne liczby, ktore maja zostac dodane do tablicy: ");
            int tmp = 1;
            while(tmp != 0)
            {
                if(scanf("%d", &tmp) != 1)
                {
                    printf("Incorrect input");
                    vector_destroy_struct(&v);
                    return 1;
                }
                if(!tmp)
                    break;
                if(vector_push_back(v, tmp) == 2)
                {
                    printf("Failed to allocate memory\n");
                    break;
                }
            }
            clear();
        }
        if(input == 2)
        {
            printf("Podaj kolejne liczby, ktore maja zostac usuniete z tablicy: ");
            int tmp = 1;
            while(tmp != 0)
            {
                if(scanf("%d", &tmp) != 1)
                {
                    printf("Incorrect input");
                    vector_destroy_struct(&v);
                    return 1;
                }
                if(tmp != 0)
                    vector_erase(v, tmp);
            }
        }
        if(input < 3 && input > 0)
            if(v->size > 0)
                vector_display(v);
            else
                printf("Buffer is empty\n");
        if(input < 0 || input > 2)
            printf("Incorrect input data\n");
    }
    vector_destroy_struct(&v);
    return 0;
}