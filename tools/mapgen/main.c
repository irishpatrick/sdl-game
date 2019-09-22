#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "cell.h"
#include "cellstack.h"

int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void gen_mods(int* arr)
{
    int r = randint(0, 3);
    int i;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    int length = 32;

    struct Grid grid;
    grid_new(&grid, length);

    int x = 10;
    int y = 0;

    struct CellStack cs;
    cs_init(&cs);

    cs_push(&cs, grid_get(&grid, x, y));

    //cs_print(&cs);

    int mods[8];

    while (cs_size(&cs) > 0)
    {
        int nx = x;
        int ny = y;
    }

    return 0;
}
