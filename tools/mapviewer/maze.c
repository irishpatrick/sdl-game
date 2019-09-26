#include "maze.h"
#include <stdlib.h>
#include <stdio.h>

static SDL_Texture* wall;
static SDL_Texture* path;
unsigned char* grid;
int gridl;

typedef struct _Point
{
    int x;
    int y;
} Point;

/*unsigned char pattern[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};*/

static Point pattern[4] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

int ind(int x, int y, int len)
{
    return (x % len) + (y * len);
}

int ctgi(int x, int y, int len)
{
    int glen = 1 + (len * 2);
    int xp = 1 + (x * 2);
    int yp = 1 + (y * 2);

    printf("new coord: (%d,%d)\n", xp, yp);

    return (xp % glen) + (yp * glen);
}

void ctgip(int* x, int* y, int len)
{
    int glen = 1 + (len * 2);
    *x = 1 + (*x * 2);
    *y = 1 + (*y * 2);
}

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
    printf("maze dimensions: %dx%d\n", (int)len, (int)len);

    unsigned char* buffer = (unsigned char*)malloc((len + 1) * len);
    fread(buffer, sizeof(unsigned char), (len + 1) * len, fp);
    
    int glen = 1 + (len * 2);
    gridl = glen;
    printf("grid dimensions: %dx%d\n", gridl, gridl);
    grid = (unsigned char*)malloc(glen * glen * sizeof(unsigned char));
    memset(grid, 1, gridl * gridl);

    int i;
    int j;
    int k;
    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < len; ++j)
        {
            grid[ctgi(j, i, len)] = 0;
            unsigned char c = buffer[ind(j, i, len)];
            unsigned char w[4];
            w[0] = (c >> 0) & 0x1;
            w[1] = (c >> 1) & 0x1;
            w[2] = (c >> 2) & 0x1;
            w[3] = (c >> 3) & 0x1;

            printf("wall: %d,%d,%d,%d\n", w[0], w[1], w[2], w[3]);

            for (k = 0; k < 4; ++k)
            {
                int xo = pattern[k].x;
                int yo = pattern[k].y;
                int x = j;
                int y = i;
                ctgip(&x, &y, len);
                printf("coord: %d,%d\n", x + xo, y + yo);
                unsigned char* p = &grid[ind(x + xo, y + yo, gridl)];
                *p = w[k];
            }
        }
    }

    free(buffer);
    fclose(fp);
}

void maze_print()
{
    if (grid == NULL)
    {
        return;
    }

    int i;
    int j;
    for (i = 0; i < gridl; ++i)
    {
        for (j = 0; j < gridl; ++j)
        {
            printf("%d ", (int)grid[ind(j, i, gridl)]);
        }
        printf("\n");
    }
}

void maze_destroy()
{
    if (grid != NULL)
    {
        free(grid);
    }
}