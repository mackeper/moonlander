#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#define sleep(X) (Sleep(X*1000))
#else
#include <unistd.h>
#endif

#include "grid.h"
#include "snake.h"
#include "coord.h"
#include "game.h"
#include "collections/list.h"

void main_game_loop(Game* game) {
    return;
    for (int i = 0; i < 1000; i++) {
        system("cls");
        game_draw(game);
        game_one_iteration(game);
        sleep(0.5);
    }
}

int main() {
    int grid_rows = 5, grid_cols = 15;
    GridItem grid_values[grid_rows*grid_cols];
    Grid grid = grid_create(grid_rows, grid_cols, grid_values);

    int snake_length = 5;
    Coord snake_positions[snake_length];
    Snake snake = snake_create(snake_length, snake_positions);

    Game game = game_create(&grid, &snake);

    main_game_loop(&game);

    // CoordList list = coordlist_create();
    // for(int i = 0; i < 100; i++) {
    //     coordlist_add(&list, (Coord) {i, i});
    //     for (size_t j = 0; j < list.lenght; j++)
    //         printf("(%d, %d) ", list.items[j].x, list.items[j].y);
    //     printf("\n");
    // }

    CoordLinkedList list = coordlinkedlist_create();
    for(int i = 0; i < 20; i++) {
        coordlinkedlist_add(&list, (Coord) {i, i});
    }
    CoordLinkedListNode* node = list.first;
    while(node != NULL) {
        printf("(%d, %d) ", node->data.x, node->data.y);
        node = node->next;
    }
    printf("\n");
    printf("%lld\n", list.length);

    CoordLinkedListNode* to_remove = coordlinkedlist_get(&list, 1);
    coordlinkedlist_remove(&list, to_remove);
    node = list.first;
    while(node != NULL) {
        printf("(%d, %d) ", node->data.x, node->data.y);
        node = node->next;
    }
    printf("\n");
    printf("%lld\n", list.length);

    return 0;
}
