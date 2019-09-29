#ifndef MAZE_H
#define MAZE_H

#include "core.h"

Maze* maze_generate(int, int);
Maze* maze_open(const char*);
void maze_save(Maze*, const char*);
Cell* maze_get(Maze*, int, int);

Grid* maze_format(Maze*, int);

void maze_free(Maze*);
void grid_free(Grid*);

#endif /* MAZE_H */ 