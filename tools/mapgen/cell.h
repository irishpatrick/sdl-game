#ifndef CELL_H
#define CELL_H

typedef struct Cell_
{
    unsigned char n;
    unsigned char s;
    unsigned char e;
    unsigned char w;
    unsigned char initial;
    unsigned char visited;
} Cell;

void cell_init(Cell*);

#endif /* CELL_H */
