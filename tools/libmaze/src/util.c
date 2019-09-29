#include "util.h"
#include <stdlib.h>
#include <time.h>

const Point pattern[4] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

static int init_rand = 0;

int randint(int min, int max)
{
    if (!init_rand)
    {
        srand(time(NULL));
        init_rand = 1;
    }
    return (rand() % (max - min + 1)) + min;
}