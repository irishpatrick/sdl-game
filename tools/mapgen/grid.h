#ifndef GRID_H
#define GRID_H

#include "cell.h"

struct Grid
{
    struct Cell* cells;
    int length;
};

struct Grid* grid_new(int);
struct Cell* grid_get(struct Grid*, int, int);
void grid_print(struct Grid*);
void grid_save(struct Grid*);
void grid_save_compact(struct Grid*);
void grid_free(struct Grid*);

#endif /* GRID_H */
