#ifndef SNAKE_GAME_
#define SNAKE_GAME_

#include "grid.h"
#include "snake.h"

typedef struct Game {
    Grid* grid;
    Snake* snake;
    int score;
} Game;

Game game_create(Grid* grid, Snake* snake);
void game_one_iteration(Game* game);
void game_draw(Game* game);

#endif // SNAKE_GAME_
