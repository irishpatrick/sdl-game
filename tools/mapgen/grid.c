#include "grid.h"
#include <stdlib.h>

void grid_new(struct Grid* grid, int length)
{
    grid = (struct Grid*)malloc(sizeof(struct Grid));
    grid->length = length;
    grid->cells = (struct Cell*)malloc(grid->length * sizeof(struct Cell));
}

struct Cell* grid_get(struct Grid* grid, int x, int y)
{
    int index = (x % grid->length) + (y * grid->length);
    return &grid->cells[index];
}
