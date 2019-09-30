#include "fmt.h"
#include "util.h"
#include "maze.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

LM_Point remap(LM_Grid* g, LM_Point p)
{
    LM_Point q;
    q.x = 1 + (p.x * 2);
    q.y = 1 + (p.y * 2);
    return q;
}

int toindex(LM_Point p, LM_Point d)
{
    return (p.x % d.x) + (p.y * d.y);
}

LM_Grid* fmt_gen(LM_Maze* m, int scale)
{
    // allocate
    
    LM_Grid* g = (LM_Grid*)malloc(sizeof(LM_Grid));
    g->scale = (uint8_t)scale;
    g->dimension.x = 1 + (m->dimension.x * 2);
    g->dimension.y = 1 + (m->dimension.y * 2);
    int cells_size = g->dimension.x * g->dimension.y;
    g->cells = (uint8_t*)malloc(cells_size * sizeof(uint8_t));
    memset(g->cells, 1, cells_size);

    // generate unscaled grid

    int i;
    int j;
    int k;
    for (i = 0; i < m->dimension.y; ++i)
    {
        for (j = 0; j < m->dimension.x; ++j)
        {
            LM_Point cp = {j, i};
            LM_Cell* c = maze_get(m, cp.x, cp.y);
            LM_Point gp = remap(g, cp);
            //printf("(%d,%d) -> 0\n", gp.x, gp.y);
            g->cells[toindex(gp, g->dimension)] = 0;

            uint8_t w[4];
            w[0] = c->e;
            w[1] = c->n;
            w[2] = c->w;
            w[3] = c->s;

            for (k = 0; k < 4; ++k)
            {
                LM_Point o = pattern[k];
                LM_Point ogp = {gp.x + o.x, gp.y + o.y};
                uint8_t* uch = &g->cells[toindex(ogp, g->dimension)];
                *uch = w[k];
                //printf("(%d,%d) -> %d\n", ogp.x, ogp.y, w[k]);
            }
            //printf("\n");
        }
    }

    // scale the grid

    if (g->scale > 1)
    {
        uint8_t* scaled_cells = (uint8_t*)malloc(g->dimension.x * g->scale * g->dimension.y * g->scale * sizeof(uint8_t));
        LM_Point scaled_dimension = {g->dimension.x * g->scale, g->dimension.y * g->scale};
        int l;

        for (i = 0; i < g->dimension.y; ++i)
        {
            for (int j = 0; j < g->dimension.x; ++j)
            {
                LM_Point orig = {j, i};
                uint8_t val = g->cells[toindex(orig, g->dimension)];
                LM_Point corner = {j * g->scale, i * g->scale};
                
                for (k = 0; k < scale; ++k)
                {
                    for (l = 0; l < scale; ++l)
                    {
                        LM_Point scaled_point = {corner.x + l, corner.y + k};
                        scaled_cells[toindex(scaled_point, scaled_dimension)] = val;
                    }
                }
            }
        }

        free(g->cells);
        g->cells = scaled_cells;
        g->dimension = scaled_dimension;
    }

    return g;
}