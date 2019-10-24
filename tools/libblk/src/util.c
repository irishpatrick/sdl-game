#include "util.h"

int get_index(BLK* b, int x, int y)
{
    return (y * b->dimension.x) + x;
}