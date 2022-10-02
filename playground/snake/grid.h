#ifndef SNAKE_GRID_
#define SNAKE_GRID_

typedef enum GridItem {
    EMPTY,
    SNAKE,
    SNAKE_HEAD,
    APPLE
} GridItem;

typedef struct Grid {
    int rows;
    int cols;
    GridItem* values;
    unsigned int size;
} Grid;

Grid grid_create(int rows, int cols, GridItem* values);
void grid_zero(Grid* grid);
GridItem grid_get_value(Grid* grid, int row, int col);
void grid_set_value(Grid* grid, int row, int col, GridItem value);
void grid_print(Grid* grid);

#endif // SNAKE_GRID_
