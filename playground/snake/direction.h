#ifndef SNAKE_DIRECTION_
#define SNAKE_DIRECTION_

#include <stdbool.h>

typedef enum {
    WEST,
    NORTH,
    EAST,
    SOUTH
} Direction;

bool direction_is_opposite(Direction dir1, Direction dir2);

#endif // SNAKE_DIRECTION_
