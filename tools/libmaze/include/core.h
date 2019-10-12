#ifndef CORE_H
#define CORE_H

#include <stdint.h>

#ifdef __cplusplus  
extern "C" { 
#endif 

typedef struct _LM_Point
{
    int x;
    int y;
} LM_Point;

typedef struct _LM_Rect
{
    int x;
    int y;
    int w;
    int h;
} LM_Rect;

typedef struct _LM_Cell
{
    uint8_t n;
    uint8_t s;
    uint8_t e;
    uint8_t w;
    uint8_t initial;
    uint8_t visited;
} LM_Cell;

typedef struct _LM_Maze
{
    LM_Cell* cells;
    LM_Point dimension;
    LM_Rect* rooms;
    int num_rooms;
} LM_Maze;

typedef struct _LM_Grid
{
    uint8_t* cells;
    LM_Point dimension;
    uint8_t scale;
} LM_Grid;

#ifdef __cplusplus 
} 
#endif 

#endif /* CORE_H */