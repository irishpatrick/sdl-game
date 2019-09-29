#include "gen.h"
#include "util.h"
#include "maze.h"
#include <stdlib.h>

// indicates an error
static const Point ep = {-1, -1};


Point extend(Maze* m, Point p)
{
    Cell* c = maze_get(m, p.x, p.y);
    uint8_t orig = c->initial;
    const Point* dir = &pattern[c->initial];
    Cell* neighbor = maze_get(m, p.x + dir->x, p.y + dir->y);

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

Point first(Maze* m, Point p)
{
    Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return ep;
    }

    c->visited = 1;
    c->initial = (uint8_t)randint(0, 3);

    return extend(m, p);
}

Point next(Maze* m, Point p)
{
    Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return ep;
    }

    c->visited = 1;
    c->initial = (c->initial + 1) % 4;

    return extend(m, p);
}

int reject(Maze* m, Point p)
{
    Cell* c = maze_get(m, p.x, p.y);
    if (c == NULL)
    {
        return 1;
    }

    Cell* neighbors[4];
    const Point* q;
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

void backtrace(Maze* m, Point p)
{
    if (reject(m, p))
    {
        return;
    }

    Point newp = first(m, p);
    while (newp.x >= 0 && newp.y >= 0)
    {
        backtrace(m, newp);
        newp = next(m, p);
    }
}

void gen_clear(Maze* m)
{
    int num_cells = m->dimension.x * m->dimension.y;
    m->cells = (Cell*)malloc(num_cells * sizeof(Cell));

    int i;
    for (i = 0; i < num_cells; ++i)
    {
        Cell* c = &m->cells[i];
        c->n = 1;
        c->e = 1;
        c->s = 1;
        c->w = 1;
        c->visited = 0;
    }
}

void gen_new(Maze* m)
{
    gen_clear(m);

    Point start;
    start.x = 0;
    start.y = 0;

    backtrace(m, start);
}