#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "grid.h"
#include "coord.h"
#include "snake.h"

static void game_recalculate_grid_(Game* game) {
    grid_zero(game->grid);
    for (int i = 1; i < game->snake->length; i++) {
        grid_set_value(game->grid, game->snake->positions[i].y, game->snake->positions[i].x, SNAKE);
    }
    grid_set_value(game->grid, game->snake->positions[0].y, game->snake->positions[0].x, SNAKE_HEAD);
}

Game game_create(Grid* grid, Snake* snake) {
    Game game = {grid, snake, 0};
    game_recalculate_grid_(&game);
    return game;
}

static Coord direction_to_coord_(Direction dir) {
    switch (dir) {
        case WEST:
            return (Coord) {-1, 0};
        case NORTH:
            return (Coord) {0, -1};
        case EAST:
            return (Coord) {1, 0};
        case SOUTH:
            return (Coord) {0, 1};
    }
    return (Coord) {0, 0};
}

static bool can_move_snake_(Game* game, Direction dir, Coord mod_coord) {
    if (direction_is_opposite(dir, game->snake->facing))
        return false;

    Coord new_head_coord = coord_mod(
        coord_add(direction_to_coord_(dir), game->snake->positions[0]),
        mod_coord
    );
    for (int i = 0; i < game->snake->length; i++)
        if (coord_equal(new_head_coord, game->snake->positions[i]))
            return false;

    return true;
}

static bool is_snake_head_on_apple(Game* game) {
    Coord head = game->snake->positions[0];
    GridItem grid_value = grid_get_value(game->grid, head.y, head.x);
    if (grid_value == APPLE)
        return true;
    return false;
}

void game_one_iteration(Game* game) {
    Coord mod_coord = { game->grid->cols, game->grid->rows };

    Direction move_dir = (Direction)(rand() % 4);
    while(!can_move_snake_(game, move_dir, mod_coord))
        move_dir = (Direction)(rand() % 4);

    snake_move(game->snake, direction_to_coord_(move_dir), mod_coord);
    if (is_snake_head_on_apple(game))
        game->score++;

    game_recalculate_grid_(game);
    printf("%d (%d, %d)\n", (int)move_dir, direction_to_coord_(move_dir).x, direction_to_coord_(move_dir).y);
    for (int i = 0; i < game->snake->length; i++)
        printf("(%d, %d) ", game->snake->positions[i].x, game->snake->positions[i].y);
    printf("\n");
}

void game_draw(Game* game) {
    printf("Score: %d\n", game->score);
    printf("| ");
    for (int x = 0; x < game->grid->cols-1; x++) {
        printf("--");
    }
    printf("- |\n");

    for (int y = 0; y < game->grid->rows; y++) {
        printf("| ");
        for (int x = 0; x < game->grid->cols; x++) {
            printf("%d ", grid_get_value(game->grid, y, x));
        }
        printf("|\n");
    }

    printf("| ");
    for (int x = 0; x < game->grid->cols-1; x++) {
        printf("--");
    }
    printf("- |\n");
}
