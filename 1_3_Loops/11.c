#include <stdio.h>
#include <math.h>

int main(void)
{
    float radius = 0;
    printf("Podaj promien kola:\n");
    while(scanf("%f", &radius) != 1 || radius <= 0)
    {
        printf("incorrect input\n");
        printf("Podaj promien kola:\n");
        getchar();
    }

    float circuit = 2 * M_PI * radius;
    float field = M_PI * radius * radius;
    printf("Obwod kola: %f\nPole kola: %f", circuit, field);
    
    return 0;
}