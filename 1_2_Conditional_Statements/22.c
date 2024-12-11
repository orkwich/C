#include <stdio.h>

int main(void)
{
    printf("Podaj liczbe z zakresu 0-10: ");
    int number = 0;

    switch(scanf("%d", &number))
    {
        case 1:
        {
            switch(number)
            {
                case 0:
                {
                    printf("zero");
                    break;
                }
                case 1:
                {
                    printf("jeden");
                    break;
                }
                case 2:
                {
                    printf("dwa");
                    break;
                }
                case 3:
                {
                    printf("trzy");
                    break;
                }
                case 4:
                {
                    printf("cztery");
                    break;
                }
                case 5:
                {
                    printf("piec");
                    break;
                }
                case 6:
                {
                    printf("szesc");
                    break;
                }
                case 7:
                {
                    printf("siedem");
                    break;
                }
                case 8:
                {
                    printf("osiem");
                    break;
                }
                case 9:
                {
                    printf("dziewiec");
                    break;
                }
                case 10:
                {
                    printf("dziesiec");
                    break;
                }
                default:
                {
                    printf("Incorrect input");
                    return 1;
                }
            }
            break;
        }
        default:
        {
            printf("Incorrect input");
            return 1;
        }
    }

    return 0;
}