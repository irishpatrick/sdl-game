#include "maze.h"
#include <stdlib.h>
#include <stdio.h>

static SDL_Texture* wall;
static SDL_Texture* path;

void maze_init(SDL_Renderer* r)
{
    SDL_Surface* wallsurf = SDL_LoadBMP("../wall.bmp");
    wall = SDL_CreateTextureFromSurface(r, wallsurf);
    SDL_FreeSurface(wallsurf);

    SDL_Surface* pathsurf = SDL_LoadBMP("../path.bmp");
    path = SDL_CreateTextureFromSurface(r, pathsurf);
    SDL_FreeSurface(pathsurf);
}

void maze_open(const char* fn)
{
    FILE* fp = fopen(fn, "rb");

    unsigned char len;
    fread(&len, sizeof(unsigned char), 1, fp);

    unsigned char* buffer = (unsigned char*)malloc((len + 1) * len);
    fread(buffer, sizeof(unsigned char), (len + 1) * len, fp);

    free(buffer);
    fclose(fp);
}