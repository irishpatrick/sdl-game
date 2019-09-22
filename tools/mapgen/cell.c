#include "cell.h"

void cell_init(struct Cell* c)
{
    c->n = 1;
    c->s = 1;
    c->e = 1;
    c->w = 1;
    c->visited = 0;
}
