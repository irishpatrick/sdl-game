#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "cell.h"
#include "cellstack.h"
#include "point.h"

int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void gen_mods(int* arr)
{
    int r = randint(0, 3);
    int i;
    for (int i = 0; i < 8; i += 2)
    {
        int dir = (r + i) % 4;
        int* x = &arr[i];
        int* y = &arr[i+1];

        switch (dir)
        {
            case 0:
                *x = 1;
                *y = 0;
                break;
            case 1:
                *x = 0;
                *y = 1;
                break;
            case 2:
                *x = -1;
                *y = 0;
                break;
            case 3:
                *x = 0;
                *y = -1;
                break;
        }
    }
}

int reject(struct Grid* grid)
{

}

int accept(struct Grid* grid)
{

}

void next(struct Grid* grid, Point point)
{

}

Point first(struct Grid* grid, Point point)
{
    Point ext;

    return ext;
}

void backtrace(struct Grid* grid, Point pt)
{
    if (reject(grid))
    {
        return;
    }

    if (accept(grid))
    {
        // done
        return;
    }

    Point point = first(grid);
    while (point.x >= 0 && point.y >= 0)
    {
        backtrace(grid, point);
        point = next(grid, point);
    }    
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
    srand(time(NULL));

    

    return 0;
}
