#ifndef CELL_H
#define CELL_H

struct Cell
{
    int n;
    int s;
    int e;
    int w;
    int visited;
};

void cell_init(struct Cell*);

#endif /* CELL_H */
