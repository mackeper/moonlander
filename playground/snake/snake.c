#include <stdlib.h>
#include <stdbool.h>

#include "snake.h"
#include "coord.h"
#include "direction.h"

Snake snake_create(int length, Coord* positions) {
    Snake s = {length, positions, EAST};
    for (int i = 0; i < s.length; i++) {
        Coord c = {s.length-i-1, 0};
        s.positions[i] = c;
    }
    return s;
}

bool snake_move(Snake* snake, Coord move_vector, Coord mod_coord) {
    Coord new_head_position = coord_mod(coord_add(snake->positions[0], move_vector), mod_coord);
    for (int i = snake->length-1; i > 0; i--)
        snake->positions[i] = snake->positions[i-1];
    snake->positions[0] = new_head_position;
    return true;
}
