#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grid.h"

Grid grid_create(int rows, int cols, GridItem* values) {
    Grid g = {rows, cols, values, g.rows*g.cols*sizeof(GridItem)};
    grid_zero(&g);
    return g;
}

void grid_zero(Grid* grid) {
    memset(grid->values, EMPTY, grid->size);
}

GridItem grid_get_value(Grid* grid, int row, int col) {
    return grid->values[grid->cols*row+col];
}

void grid_set_value(Grid* grid, int row, int col, GridItem value) {
    grid->values[grid->cols*row+col] = value;
}

void grid_print(Grid* grid) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 5; c++) {
            printf(" %d", grid_get_value(grid, r, c));
        }
        printf("\n");
    }
}
