#include <stdio.h>

int main(void)
{
    printf("Your choice: ");
    char choic = '\0';
    scanf("%c", &choic);

    char *output[3] = {"Breakfast, Lunch and Dinner", "Lunch and Dinner", "Dinner"};

    switch(choic == 'A' || choic == 'B' || choic == 'C')
    {
        case 0:
        {
            printf("Incorrect input\n");
            return 1;
        }
    }

    int index = 0;
    switch(choic)
    {
        case 'C':
            index++;
        case 'B':
            index++;
        case 'A':
            index++;
    }
    printf("You chose %s as your meal plan.", output[index - 1]);
    return 0;
}