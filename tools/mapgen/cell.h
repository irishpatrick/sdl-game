#ifndef CELL_H
#define CELL_H

struct Cell
{
    unsigned char n;
    unsigned char s;
    unsigned char e;
    unsigned char w;
    unsigned char initial;
    unsigned char visited;
};

void cell_init(struct Cell*);

#endif /* CELL_H */
