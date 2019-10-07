#ifndef MAZE_H
#define MAZE_H

#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif 

LM_Maze* maze_generate_with_rooms(int, int);
LM_Maze* maze_generate(int, int);
LM_Maze* maze_open(const char*);
int maze_remove_wall(LM_Maze*, int, int, int, int);
void maze_save(LM_Maze*, const char*);
void grid_save(LM_Grid*, const char*);
LM_Cell* maze_get(LM_Maze*, int, int);
uint8_t grid_get(LM_Grid*, int, int);
uint8_t* grid_getp(LM_Grid*, int, int);

LM_Grid* maze_format(LM_Maze*, int);
int grid_format(LM_Grid*, int);
int grid_space(LM_Grid*, int);

void maze_free(LM_Maze*);
void grid_free(LM_Grid*);

#ifdef __cplusplus
}
#endif

#endif /* MAZE_H */ 