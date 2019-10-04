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

int fmt_mod(LM_Grid* g, int scale)
{
    uint8_t* modified = (uint8_t*)malloc(g->dimension.x * scale * g->dimension.y * scale * sizeof(uint8_t));

    LM_Point sd = {g->dimension.x * scale, g->dimension.y * scale};

    int i;
    int j;
    int k;
    int l;
    for (i = 0; i < g->dimension.y; ++i)
    {
        for (j = 0; j < g->dimension.x; ++j)
        {
            LM_Point orig = {j, i};
            int ind = toindex(orig, g->dimension);
            uint8_t val = g->cells[ind];
            for (k = 0; k < scale; ++k)
            {
                for (l = 0; l < scale; ++l)
                {
                    LM_Point target = {(orig.x * scale) + l, (orig.y * scale) + k};
                    ind = toindex(target, sd);
                    modified[ind] = val;
                }
            }
        }
    }

    g->dimension.x = g->dimension.x * scale;
    g->dimension.y = g->dimension.y * scale;
    uint8_t* trash = g->cells;
    g->cells = modified;
    free(trash);
    return 0;
}

void trim_walls(LM_Grid* g, LM_Point p)
{
    int i;
    for (i = 0; i < 4; ++i)
    {
        uint8_t* vp = grid_getp(g, p.x + pattern[i].x, p.y + pattern[i].y);
        if (*vp == 1)
        {
            *vp = 0;
        }
    }
}

void connect(uint8_t* arr, LM_Point p, LM_Point d)
{
    
}

int fmt_space(LM_Grid* g, int spacing)
{
    /*fmt_mod(g, spacing);

    int i;
    int j;
    for (i = 0; i < g->dimension.y; ++i)
    {
        for (j = 0; j < g->dimension.x; ++j)
        {
            uint8_t val = grid_get(g, j, i);
            if (val == 0)
            {
                LM_Point cur = {j, i};
                trim_walls(g, cur);
            }
        }
    }*/

    LM_Point newd = {g->dimension.x * spacing, g->dimension.y * spacing};
    uint8_t* modified = (uint8_t*)malloc(newd.x * newd.y * sizeof(uint8_t));
    memset(modified, 2, newd.x * newd.y * sizeof(uint8_t));

    int i;
    int j;
    for (i = 0; i < g->dimension.y; ++i)
    {
        for (j = 0; j < g->dimension.x; ++j)
        {
            LM_Point newp = {j * spacing, i * spacing};
            int index = toindex(newp, newd);
            modified[index] = grid_get(g, j, i);
        }
    }

    // connect all the floating points, unless a wall exists between them
    for (i = 0; i < newd.y; ++i)
    {
        for (j = 0; j < newd.x; ++j)
        {
            LM_Point newp = {j, i};
            uint8_t val = modified[toindex(newp, newd)];
            if (val == 0)
            {
                connect(modified, newp, newd);
            }
        }
    }

    g->dimension.x = g->dimension.x * spacing;
    g->dimension.y = g->dimension.y * spacing;
    uint8_t* trash = g->cells;
    g->cells = modified;
    free(trash);

    return 0;
}