#ifndef MAZE_H
#define MAZE_H

#include <SDL.h>

typedef struct _Cell
{

} Cell;

void maze_init(SDL_Renderer*);
void maze_open(const char*);
void maze_print();
void maze_destroy();

#endif /* MAZE_H */