#ifndef GRID_H
#define GRID_H

#include "cell.h"

struct Grid
{
    struct Cell* cells;
    int length;
};

void grid_new(struct Grid*, int);
struct Cell* grid_get(struct Grid*, int, int);

#endif /* GRID_H */
