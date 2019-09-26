#include "grid.h"
#include "point.h"
#include <stdlib.h>
#include <stdio.h>

struct Grid* grid_new(int length)
{
    struct Grid* grid;
    grid = (struct Grid*)malloc(sizeof(struct Grid));
    grid->length = length;
    grid->cells = (struct Cell*)malloc(grid->length * grid->length * sizeof(struct Cell));
    if (grid->cells == NULL)
    {
        printf("out of memory\n");
        exit(1);
    }
    int i;
    for (i = 0; i < grid->length * grid->length; ++i)
    {
        cell_init(&grid->cells[i]);
    }
    return grid;
}

struct Cell* grid_get(struct Grid* grid, int x, int y)
{
    if (x < 0 || y < 0 || x >= grid->length || y >= grid->length)
    {
        return NULL;
    }
    int index = (x % grid->length) + (y * grid->length);
    return &grid->cells[index];
}

void grid_print(struct Grid* grid)
{
    int i;
    int j;
    for (i = 0; i < grid->length; ++i)
    {
        for (j = 0; j < grid->length; ++j)
        {
            // [^v] indicates all walls
            //  ^v  n and s, no e and w walls

            Point p = {j, i};
            struct Cell* c = grid_get(grid, p.x, p.y);
            char v = ':';
            if (c->visited)
            {
                v = ';';
            }
            if (c == NULL)
            {
                printf("grid_print: null pointer error\n");
            }

            if (c->w)
            {
                printf("[");
            }
            else
            {
                printf("%c", v);
            }

            if (c->n)
            {
                printf("^");
            }
            else
            {
                printf(".");
            }

            if (c->s)
            {
                printf("v");
            }
            else
            {
                printf(".");
            }

            if (c->e)
            {
                printf("]");
            }
            else
            {
                printf("%c", v);
            }
        }

        printf("\n");
    }
}

void grid_save(struct Grid* grid)
{
    FILE* fp = fopen("out.txt", "w");

    int i;
    int j;
    for (i = 0; i < grid->length; ++i)
    {
        for (j = 0; j < grid->length; ++j)
        {
            // [^v] indicates all walls
            //  ^v  n and s, no e and w walls

            Point p = {j, i};
            struct Cell* c = grid_get(grid, p.x, p.y);
            char v = ':';
            if (c->visited)
            {
                v = ';';
            }
            if (c == NULL)
            {
                printf("grid_print: null pointer error\n");
            }

            if (c->w)
            {
                fprintf(fp, "[");
            }
            else
            {
                fprintf(fp, "%c", v);
            }

            if (c->n)
            {
                fprintf(fp, "^");
            }
            else
            {
                fprintf(fp, ".");
            }

            if (c->s)
            {
                fprintf(fp, "v");
            }
            else
            {
                fprintf(fp, ".");
            }

            if (c->e)
            {
                fprintf(fp, "]");
            }
            else
            {
                fprintf(fp, "%c", v);
            }
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

void grid_save_compact(struct Grid* grid)
{
    const char E = 0x1;
    const char N = 0x2;
    const char W = 0x4;
    const char S = 0x8;
    const char newl = 0xFF;

    FILE* fp = fopen("out.hex", "wb");
    char* buffer = (char*)malloc(sizeof(int) + ((grid->length + 1) * grid->length));

    // fill buffer
    unsigned char cl = (unsigned char)grid->length;
    fwrite(&cl, sizeof(unsigned char), 1, fp);

    int pos = 0;
    int i;
    int j;
    for (i = 0; i < grid->length; ++i)
    {
        for (j = 0; j < grid->length; ++j)
        {
            struct Cell* c = grid_get(grid, j, i);
            char val = 0;
            if (c->e)
            {
                val = val | E;
            }
            if (c->n)
            {
                val = val | N;
            }
            if (c->w)
            {
                val = val | W;
            }
            if (c->s)
            {
                val = val | S;
            }

            buffer[pos++] = val;
        }
        buffer[pos++] = newl;
    }

    fwrite(buffer, sizeof(char), (grid->length + 1) * grid->length, fp);
    fclose(fp);
    free(buffer);
}

void grid_free(struct Grid* grid)
{
    if (grid == NULL)
    {
        return;
    }

    free(grid);
}
