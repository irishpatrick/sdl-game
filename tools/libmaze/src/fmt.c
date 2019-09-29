#include "fmt.h"
#include "util.h"
#include "maze.h"
#include <stdlib.h>
#include <string.h>

Point remap(Grid* g, Point p)
{
    Point q;
    q.x = 1 + (p.x * 2);
    q.y = 1 + (p.y * 2);
    return q;
}

int toindex(Point p, Point d)
{
    return (p.x % d.x) + (p.y * d.y);
}

Grid* fmt_gen(Maze* m, int padding)
{
    Grid* g = (Grid*)malloc(sizeof(Grid));
    g->dimension.x = (1 + m->dimension.x) * 2;
    g->dimension.y = (1 + m->dimension.y) * 2;
    int cells_size = g->dimension.x * g->dimension.y * sizeof(uint8_t);
    g->cells = (uint8_t*)malloc(cells_size);
    memset(g->cells, 1, cells_size);

    int i;
    int j;
    int k;
    for (i = 0; i < m->dimension.y; ++i)
    {
        for (j = 0; j < m->dimension.x; ++j)
        {
            Point cp = {j, i};
            Cell* c = maze_get(m, cp.x, cp.y);
            Point gp = remap(g, cp);
            g->cells[toindex(gp, g->dimension)] = 0;

            uint8_t w[4];
            w[0] = c->e;
            w[1] = c->n;
            w[2] = c->s;
            w[3] = c->w;

            for (k = 0; k < 4; ++k)
            {
                Point o = pattern[k];
                Point ogp = {gp.x + o.x, gp.y + o.y};
                uint8_t* uch = &g->cells[toindex(ogp, g->dimension)];
                *uch = w[k];
            }
        }
    }

    return g;
}