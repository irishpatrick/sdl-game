#include "boundingbox.h"

int box_collision(Box* a, Box* b)
{
    if (
        a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y
    )
    {
        return 1;
    }

    return 0;
}