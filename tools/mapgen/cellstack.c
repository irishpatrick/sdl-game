#include "cellstack.h"
#include <stdlib.h>
#include <stdio.h>

void cs_init(struct CellStack* cs)
{
    cs->head = NULL;
}

void cs_push(struct CellStack* cs, struct Cell* cell)
{
    struct Node** node = &cs->head;

    while (*node != NULL)
    {
        *node = (*node)->next;
    }

    *node = (struct Node*)malloc(sizeof(struct Node));
    (*node)->next = NULL;
    (*node)->cell = cell;
}

struct Cell* cs_pop(struct CellStack* cs)
{
    struct Node** node = &cs->head;
    struct Node* prev = NULL;
    struct Cell* ret = NULL;

    if (*node == NULL)
    {
        return NULL;
    }

    while ((*node)->next != NULL)
    {
        prev = *node;
        *node = (*node)->next;
    }

    ret = (*node)->cell;
    free(*node);
    *node = NULL;
    if (prev != NULL)
    {
        prev->next = NULL;
    }
    
    return ret;
}

int cs_size(struct CellStack* cs)
{
    int size = 0;
    struct Node* node = cs->head;

    while (node != NULL)
    {
        ++size;
        node = node->next;
    }

    return size;
}

void cs_print(struct CellStack* cs)
{
    struct Node* node = cs->head;
    while (node != NULL)
    {
        printf("node->");
        node = node->next;
    }
    printf("\n");
}
