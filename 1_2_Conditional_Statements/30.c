#include <stdio.h>

int main(void)
{
    printf("Podaj ocene: ");
    int note = 0;
    scanf("%d", &note);
    switch(note)
    {
        case 1:
            printf("Brak promocji do nastepnej klasy\n");
            break;
        
        case 2:
            printf("Promocja do nastepnej klasy\n");
            break;
        
        case 3:
            printf("Promocja do nastepnej klasy\n");
            break;
        
        case 4:
            printf("Promocja do nastepnej klasy\n");
            break;
        
        case 5:
            printf("Promocja do nastepnej klasy\n");
            break;
        
        case 6:
            printf("Promocja z ocena celujaca\n");
            break;

        default:
            printf("Wprowadzona ocena jest niepoprawna");
    }
    return 0;
}