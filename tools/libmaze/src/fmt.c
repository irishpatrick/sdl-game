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
    if (g == NULL)
    {
        return NULL;
    }
    g->scale = (uint8_t)scale;
    g->dimension.x = 1 + (m->dimension.x * 2);
    g->dimension.y = 1 + (m->dimension.y * 2);
    int cells_size = g->dimension.x * g->dimension.y;
    g->cells = (uint8_t*)malloc(cells_size * sizeof(uint8_t));
    if (g->cells == NULL)
    {
        free(g);
        return NULL;
    }
    memset(g->cells, 1, cells_size);

    // generate unscaled grid

    int i;
    int j;
    int k;
    for (i = 0; i < m->dimension.y; ++i)
    {
        for (j = 0; j < m->dimension.x; ++j)
        {
            LM_Point current_pt = {j, i};
            LM_Cell* cell = maze_get(m, current_pt.x, current_pt.y);
            LM_Point grid_pt = remap(g, current_pt);
            g->cells[toindex(grid_pt, g->dimension)] = 0;

            uint8_t w[4];
            w[0] = cell->e;
            w[1] = cell->n;
            w[2] = cell->w;
            w[3] = cell->s;

            for (k = 0; k < 4; ++k)
            {
                LM_Point orig = pattern[k];
                LM_Point orig_grid_pt = {grid_pt.x + orig.x, grid_pt.y + orig.y};
                uint8_t* value = &g->cells[toindex(orig_grid_pt, g->dimension)];
                *value = w[k];
            }
        }
    }

    // fill in the rooms

    if (m->rooms != NULL)
    {
        for (i = 0; i < m->num_rooms; ++i) // TODO: fix bounds
        {
            LM_Rect* room = &m->rooms[i];
            for (j = 0; j < room->h; ++j)
            {
                for (k = 0; k < room->w; ++k)
                {
                    LM_Point pt = { room->x + k, room->y + j };

                    int perimeter = (
                        (pt.x == room->x)               * 1     +
                        (pt.x == room->x + room->w - 1) * 10    +
                        (pt.y == room->y)               * 100   + 
                        (pt.y == room->y + room->h - 1) * 1000
                    );
                    //printf("PERIMETER: %.4d\n", perimeter);

                    if (perimeter > 0)
                    {

                    }

                    LM_Point grid_pt = remap(g, pt);
                    g->cells[toindex(grid_pt, g->dimension)] = 0;

                    LM_Point grid_pt_s = grid_pt;
                    grid_pt_s.y += 1;
                    LM_Point grid_pt_w = grid_pt;
                    grid_pt_w.x += 1;
                    LM_Point diag = grid_pt;
                    diag.x += 1;
                    diag.y += 1;

                    uint8_t* south = &g->cells[toindex(grid_pt_s, g->dimension)];
                    uint8_t* west = &g->cells[toindex(grid_pt_w, g->dimension)];
                    uint8_t* southwest = &g->cells[toindex(diag, g->dimension)];
                    
                    int south_ok = j < room->h - 1;
                    int west_ok = k < room->w - 1;
                    
                    if (south_ok)
                    {
                        *south = 0;
                    }
                    if (west_ok)
                    {
                        *west = 0;
                    }
                    if (south_ok && west_ok)
                    {
                        *southwest = 0;
                    }
                }
            }
        }
    }

    // scale the grid

    if (g->scale > 1)
    {
        uint8_t* scaled_cells = (uint8_t*)malloc(g->dimension.x * g->scale * g->dimension.y * g->scale * sizeof(uint8_t));
        if (scaled_cells == NULL)
        {
            return NULL;
        }

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
    if (modified == NULL)
    {
        return 1;
    }

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
    if (modified == NULL)
    {
        return 1;
    }
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