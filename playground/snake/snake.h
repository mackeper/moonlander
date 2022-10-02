#ifndef SNAKE_SNAKE_
#define SNAKE_SNAKE_

#include "coord.h"
#include "direction.h"

typedef struct Snake {
    int length;
    Coord* positions;
    Direction facing;
} Snake;

Snake snake_create(int length, Coord* positions);
bool snake_move(Snake* snake, Coord move_vector, Coord mod_coord);

#endif // SNAKE_SNAKE_
