#include "gen.h"
#include "util.h"
#include "maze.h"
#include <stdlib.h>

// indicates an error
static const LM_Point ep = {-1, -1};


LM_Point extend(LM_Maze* m, LM_Point p)
{
    LM_Cell* c = maze_get(m, p.x, p.y);

    uint8_t orig = c->initial;
    const LM_Point* dir = &pattern[c->initial];
    LM_Cell* neighbor = maze_get(m, p.x + dir->x, p.y + dir->y);

    while (neighbor == NULL || neighbor->visited)
    {
        c->initial = (c->initial + 1) % 4;
        if (c->initial == orig)
        {
            return ep;
        }
        dir = &pattern[c->initial];
        neighbor = maze_get(m, p.x + dir->x, p.y + dir->y);
    }

    if (neighbor == NULL)
    {
        return ep;
    }
    
    neighbor->visited = 1;
    switch(c->initial)
    {
        case 0:
        c->e = 0;
        neighbor->w = 0;
        break;

        case 1:
        c->n = 0;
        neighbor->s = 0;
        break;

        case 2:
        c->w = 0;
        neighbor->e = 0;
        break;

        case 3:
        c->s = 0;
        neighbor->n = 0;
        break;
    }

    p.x += dir->x;
    p.y += dir->y;

    return p;
}

LM_Point first(LM_Maze* m, LM_Point p)
{
    LM_Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return ep;
    }

    c->visited = 1;
    c->initial = (uint8_t)randint(0, 3);

    return extend(m, p);
}

LM_Point next(LM_Maze* m, LM_Point p)
{
    LM_Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return ep;
    }

    c->visited = 1;
    c->initial = (c->initial + 1) % 4;

    return extend(m, p);
}

int reject(LM_Maze* m, LM_Point p)
{
    LM_Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return 1;
    }

    LM_Cell* neighbors[4];
    const LM_Point* q;
    int ret = 0;

    int i;
    for (i = 0; i < 4; ++i)
    {
        q = &pattern[i];
        neighbors[i] = maze_get(m, p.x + q->x, p.y + q->y);
        if (neighbors[i] != NULL)
        {
            ret += neighbors[i]->visited;
        }
        else
        {
            ret += 1;
        }
    }

    return ret > 3;
}

void backtrace(LM_Maze* m, LM_Point p)
{
    if (reject(m, p))
    {
        return;
    }

    LM_Point newp = first(m, p);
    while (newp.x >= 0 && newp.y >= 0)
    {
        backtrace(m, newp);
        newp = next(m, p);
    }
}

void gen_clear(LM_Maze* m)
{
    int num_cells = m->dimension.x * m->dimension.y;
    m->cells = (LM_Cell*)malloc(num_cells * sizeof(LM_Cell));

    int i;
    for (i = 0; i < num_cells; ++i)
    {
        LM_Cell* c = &m->cells[i];
        c->n = 1;
        c->e = 1;
        c->s = 1;
        c->w = 1;
        c->visited = 0;
        c->initial = 0;
    }
}

void gen_new(LM_Maze* m)
{
    gen_clear(m);

    LM_Point start;
    start.x = 0;
    start.y = 0;

    backtrace(m, start);
}