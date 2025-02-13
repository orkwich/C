#include "board.h"

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int main(void)
{
    printf("Enter width and height of the board: ");
    int width = 0;
    int height = 0;
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input");
        return 1;
    }
    if(width <= 0 || height <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct board_t *board;
    if(create_board(&board, width, height) != 0)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter player's initial coordinates (x, y): ");
    int x = 0;
    int y = 0;
    if(scanf("%d %d", &x, &y) != 2)
    {
        printf("Incorrect input");
        free_board(board);
        return 1;
    }
    if(x < 0 || x >= width || y < 0 || y >= height)
    {
        printf("Incorrect input data");
        free_board(board);
        return 2;
    }
    set_player(board, x, y);
    char choice = '\0';
    clear();
    display_board(board);
    while(choice != 'q')
    {
        printf("Choose your action: ");
        scanf("%c", &choice);
        clear();
        if(choice == 'q')
            break;
        else if(choice == 'w')
            board->move_player_up(board);
        else if(choice == 's')
            board->move_player_down(board);
        else if(choice == 'a')
            board->move_player_left(board);
        else if(choice == 'd')
            board->move_player_right(board);
        else
        {
            printf("Incorrect choice\n");
            continue;
        }
        display_board(board);
    }
    free_board(board);
    return 0;
}