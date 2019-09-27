#ifndef GRID_H
#define GRID_H

#include "cell.h"

typedef struct Grid_
{
    Cell* cells;
    int length;
} Grid;

Grid* grid_new(int);
Cell* grid_get(Grid*, int, int);
void grid_print(Grid*);
void grid_save(Grid*);
void grid_save_compact(Grid*);
void grid_free(Grid*);

#endif /* GRID_H */
