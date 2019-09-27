#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "cell.h"

struct Node
{
    struct Node* next;
    Cell* cell;
};

struct CellStack
{
    struct Node* head;
};

void cs_print(struct CellStack*);
void cs_init(struct CellStack*);
void cs_push(struct CellStack*, Cell*);
Cell* cs_pop(struct CellStack*);
int cs_size(struct CellStack*);

#endif /* CELLSTACK_H */
