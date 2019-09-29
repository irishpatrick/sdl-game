#include "maze.h"
#include "gen.h"
#include "fmt.h"
#include <stdlib.h>
#include <stdio.h>

Maze* maze_generate(int w, int h)
{
    Maze* m = (Maze*)malloc(sizeof(Maze));
    
    Point p = {w, h};
    m->dimension = p;
    m->cells = NULL;

    gen_new(m);

    return m;
}

Grid* maze_format(Maze* m, int padding)
{
    return fmt_gen(m, padding);
}

Maze* maze_open(const char* fn)
{
    Maze* m = (Maze*)malloc(sizeof(Maze));

    FILE* fp = fopen(fn, "rb");
    if (!fp)
    {
        free(m);
        return NULL;
    }

    fread(&m->dimension.x, sizeof(uint8_t), 1, fp);
    fread(&m->dimension.y, sizeof(uint8_t), 1, fp);

    int buffer_size = m->dimension.x * m->dimension.y;
    uint8_t* buffer = (uint8_t*)malloc(buffer_size * sizeof(uint8_t));
    fread(buffer, sizeof(uint8_t), buffer_size, fp);

    int i;
    for (i = 0; i < buffer_size; ++i)
    {
        uint8_t ch = buffer[i];
        Cell* c = &m->cells[i];
        c->visited = 1;
        c->e = (ch >> 0) & 0x1;
        c->n = (ch >> 1) & 0x1;
        c->w = (ch >> 2) & 0x1;
        c->s = (ch >> 3) & 0x1;
    }

    free(buffer);
    fclose(fp);
    
    return m;
}

void maze_save(Maze* m, const char* fn)
{
    const char E = 0x1;
    const char N = 0x2;
    const char W = 0x4;
    const char S = 0x8;

    FILE* fp = fopen(fn, "wb");

    // write header
    fwrite(&m->dimension.x, sizeof(uint8_t), 1, fp);
    fwrite(&m->dimension.y, sizeof(uint8_t), 1, fp);

    int len = m->dimension.x * m->dimension.y;
    
    int i;
    for (i = 0; i < len; ++i)
    {
        Cell* c = &m->cells[i];
        uint8_t ch = 0;

        if (c->e)
        {
            ch |= E;
        }
        if (c->n)
        {
            ch |= N;
        }
        if (c->w)
        {
            ch |= W;
        }
        if (c->s)
        {
            ch |= S;
        }

        fwrite(&ch, sizeof(uint8_t), 1, fp);
    }

    fclose(fp);
}

Cell* maze_get(Maze* m, int x, int y)
{
    if (x < 0 || y < 0 || x >= m->dimension.x || y >= m->dimension.y)
    {
        return NULL;
    }
    int index = (x % m->dimension.x) + (y * m->dimension.y);
    return &m->cells[index];
}

void maze_free(Maze* m)
{
    if (m != NULL)
    {
        if (m->cells != NULL)
        {
            free(m->cells);
        }
        free(m);
    }
}

void grid_free(Grid* g)
{
    if (g != NULL)
    {
        if (g->cells != NULL)
        {
            free(g->cells);
        }
        free(g);
    }
}