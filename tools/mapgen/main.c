#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "cell.h"
#include "cellstack.h"
#include "point.h"

const Point pattern[] = {
    {1, 0}, 
    {0, -1}, 
    {-1, 0}, 
    {0, 1}
};

const Point pe = {-1, -1};

int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int reject(Grid* grid, Point point)
{
    //printf("reject: get cell at point [%d,%d]\n", point.x, point.y);
    Cell* c = grid_get(grid, point.x, point.y);
    if (c == NULL)
    {
        printf("error: cell was null\n");
        return 1;
    }

    Cell* neighbors[4];
    const Point* p;
    int ret = 0;

    int i;
    for (i = 0; i < 4; ++i)
    {
        p = &pattern[i];
        neighbors[i] = grid_get(grid, point.x + p->x, point.y + p->y);
        if (neighbors[i] != NULL)
        {
            ret += neighbors[i]->visited;
        }
        else
        {
            ret += 1;
        }
    }

    //printf("reject: %d unvisited neighbors\n", 4 - ret);

    return ret > 3;
}

Point next(Grid* grid, Point point)
{
    Cell* c = grid_get(grid, point.x, point.y);
    if (c == NULL)
    {
        return pe;
    }
    
    c->visited = 1;
    c->initial = (c->initial + 1) % 4;
    unsigned char orig = c->initial;

    const Point* dir = &pattern[c->initial];
    Cell* neighbor = grid_get(grid, point.x + dir->x, point.y + dir->y);
    while (neighbor == NULL || neighbor->visited)
    {
        c->initial = (c->initial + 1) % 4;
        if (c->initial == orig)
        {
            //printf("fatal error\n");
            return pe;
        }
        dir = &pattern[c->initial];
        neighbor = grid_get(grid, point.x + dir->x, point.y + dir->y);
    }
    
    if (neighbor == NULL)
    {
        printf("error: neighbor was null\n");
        return pe;
    }

    neighbor->visited = 1;

    // remove walls between cells
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
    }

    //printf("\tdir [%d,%d]\n", dir->x, dir->y);
    point.x += dir->x;
    point.y += dir->y;

    return point;
}

Point first(Grid* grid, Point point)
{
    Cell* c = grid_get(grid, point.x, point.y);
    if (c == NULL)
    {
        //printf("error: cell was null\n");
        return pe;
    }

    c->visited = 1;
    c->initial = (unsigned char)randint(0, 3);
    unsigned char orig = c->initial;
    const Point* dir = &pattern[c->initial];
    Cell* neighbor = grid_get(grid, point.x + dir->x, point.y + dir->y);
    
    while (neighbor == NULL || neighbor->visited)
    {
        c->initial = (c->initial + 1) % 4;
        if (c->initial == orig)
        {
            //printf("fatal error\n");
            return pe;
        }
        dir = &pattern[c->initial];
        neighbor = grid_get(grid, point.x + dir->x, point.y + dir->y);
    }
    
    if (neighbor == NULL)
    {
        //printf("error: neighbor was null\n");
        return pe;
    }

    //printf("first: choosing direction %d\n", c->initial);

    neighbor->visited = 1;

    // remove walls between cells
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

    //printf("\tdir [%d,%d]\n", dir->x, dir->y);

    point.x += dir->x;
    point.y += dir->y;

    //printf("first: [%d,%d]\n", point.x, point.y);

    return point;
}

void backtrace(Grid* grid, Point pt)
{
    //printf("point: [%d,%d]\n", pt.x, pt.y);
    //grid_print(grid);
    //printf("\n\n");

    if (reject(grid, pt))
    {
        //printf("reject\n");
        return;
    }

    Point point = first(grid, pt);
    //printf("first point: [%d,%d] -> [%d,%d]\n", pt.x, pt.y, point.x, point.y);
    while (point.x >= 0 && point.y >= 0)
    {
        //printf("bt with: [%d,%d]\n", point.x, point.y);
        backtrace(grid, point);
        point = next(grid, pt);
        //printf("next point: [%d,%d]\n", point.x, point.y);
        //grid_print(grid);
        //printf("\n\n");
        //printf("next\n");
    }

    //printf("return\n");
}

/**
 * plan
 * pick start cell
 * pick next
 * validate
 * next
 * validate
 * next validate
 * 
 * if validate fails
 * return
 */

int main(int argc, char** argv)
{
    int dim = 8;
    if (argc > 1)
    {
        dim = atoi(argv[1]);
    }

    srand(time(NULL));

    Point start;
    start.x = 0;
    start.y = 0;

    Grid* grid = grid_new(dim);
    if (grid == NULL)
    {
        printf("cannot malloc grid\n");
        exit(1);
    }

    printf("generating... ");
    fflush(stdout);
    backtrace(grid, start);
    printf("done\n");

    printf("saving... ");
    fflush(stdout);
    grid_save_compact(grid);
    printf("done\n");

    grid_free(grid);

    return 0;
}
