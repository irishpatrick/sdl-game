#ifndef CORE_H
#define CORE_H

#include <stdint.h>

typedef struct _Point
{
    int x;
    int y;
} Point;

typedef struct _Cell
{
    uint8_t n;
    uint8_t s;
    uint8_t e;
    uint8_t w;
    uint8_t initial;
    uint8_t visited;
} Cell;

typedef struct _Maze
{
    Cell* cells;
    Point dimension;
} Maze;

typedef struct _Grid
{
    uint8_t* cells;
    Point dimension;
} Grid;

#endif /* CORE_H */