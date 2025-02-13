#include "board.h"

int create_board(struct board_t **board, int width, int height)
{
    if(board == NULL || width <= 0 || height <= 0)
        return 1;
    *board = malloc(sizeof(struct board_t));
    if(*board == NULL)
        return 2;
    (*board)->board = malloc(sizeof(char *) * height);
    if((*board)->board == NULL)
    {
        free(*board);
        *board = NULL;
        return 2;
    }
    for(int i = 0; i < height; i++)
    {
        *((*board)->board + i) = malloc(sizeof(char) * (width + 1));
        if(*((*board)->board + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*((*board)->board + i));
            free((*board)->board);
            free(*board);
            *board = NULL;
            return 2;
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            *(*((*board)->board + i) + j) = '.';
        *(*((*board)->board + i) + width) = '\0';
    }
    (*board)->height = height;
    (*board)->width = width;
    (*board)->is_init = 0;
    (*board)->player.x = 0;
    (*board)->player.y = 0;
    (*board)->move_player_down = &move_player_down;
    (*board)->move_player_left = &move_player_left;
    (*board)->move_player_up = &move_player_up;
    (*board)->move_player_right = &move_player_right;
    return 0;
}

void display_board(const struct board_t *board)
{
    if(board == NULL || board->height <= 0 || board->width <= 0)
        return;
    for(int i = 0; i < board->height; i++)
        printf("%s\n", *(board->board + i));
}

void free_board(struct board_t *board)
{
    if(board == NULL || board->height <= 0 || board->width <= 0)
        return;
    for(int i = 0; i < board->height; i++)
        free(*(board->board + i));
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y)
{
    if(board == NULL || board->board == NULL || board->is_init == 1 || board->height <= 0 || board->width <= 0 || x < 0 || y < 0 || board->height <= y || board->width <= x)
        return 1;
    board->player.x = x;
    board->player.y = y;
    board->is_init = 1;
    *(*(board->board + y) + x) = '@';
    return 0;
}

struct board_t* move_player_up(struct board_t *board)
{
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0)
        return NULL;
    for(int i = 0; i < board->height; i++)
    {
        for(int j = 0; j < board->width; j++)
        {
            if(*(*(board->board + i) + j) == '@')
            {
                if(board->player.x != j || board->player.y != i)
                    return NULL;
                *(*(board->board + i) + j) = '.';
                if(i == 0)
                {
                    *(*(board->board + board->height - 1) + j) = '@';
                    board->player.y = board->height - 1;
                }
                else
                {
                    *(*(board->board + i - 1) + j) = '@';
                    board->player.y = i - 1;
                }
                return board;
            }
        }
    }
    return NULL;
}

struct board_t* move_player_down(struct board_t *board)
{
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0)
        return NULL;
    for(int i = 0; i < board->height; i++)
    {
        for(int j = 0; j < board->width; j++)
        {
            if(*(*(board->board + i) + j) == '@')
            {
                if(board->player.x != j || board->player.y != i)
                    return NULL;
                *(*(board->board + i) + j) = '.';
                if(i == board->height - 1)
                {
                    *(*(board->board) + j) = '@';
                    board->player.y = 0;
                }
                else
                {
                    *(*(board->board + i + 1) + j) = '@';
                    board->player.y = i + 1;
                }
                return board;
            }
        }
    }
    return NULL;
}

struct board_t* move_player_left(struct board_t *board)
{
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0)
        return NULL;
    for(int i = 0; i < board->height; i++)
    {
        for(int j = 0; j < board->width; j++)
        {
            if(*(*(board->board + i) + j) == '@')
            {
                if(board->player.x != j || board->player.y != i)
                    return NULL;
                *(*(board->board + i) + j) = '.';
                if(j == 0)
                {
                    *(*(board->board + i) + board->width - 1) = '@';
                    board->player.x = board->width - 1;
                }
                else
                {
                    *(*(board->board + i) + j - 1) = '@';
                    board->player.x = j - 1;
                }
                return board;
            }
        }
    }
    return NULL;
}

struct board_t* move_player_right(struct board_t *board)
{
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0)
        return NULL;
    for(int i = 0; i < board->height; i++)
    {
        for(int j = 0; j < board->width; j++)
        {
            if(*(*(board->board + i) + j) == '@')
            {
                if(board->player.x != j || board->player.y != i)
                    return NULL;
                *(*(board->board + i) + j) = '.';
                if(j == board->width - 1)
                {
                    *(*(board->board + i)) = '@';
                    board->player.x = 0;
                }
                else
                {
                    *(*(board->board + i) + j + 1) = '@';
                    board->player.x = j + 1;
                }
                return board;
            }
        }
    }
    return NULL;
}