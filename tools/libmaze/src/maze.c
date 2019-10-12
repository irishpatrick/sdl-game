#include "maze.h"
#include "gen.h"
#include "fmt.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int overlap(LM_Rect a, LM_Rect b)
{
    return 
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y;
}

int maze_remove_wall(LM_Maze* m, int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    if (dx != 0 && dy != 0 || fabs(dx) > 1 || fabs(dy) > 1)
    {
        return 1;
    }

    LM_Cell* c1 = maze_get(m, x1, y1);
    LM_Cell* c2 = maze_get(m, x2, y2);

    if (dx < 0) // east
    {
        c1->e = 0;
        c2->w = 0;
    }
    else if (dx > 0) // west
    {
        c1->w = 0;
        c2->e = 0;
    }
    else if (dy < 0) // south
    {
        c1->s = 0;
        c2->n = 0;
    }
    else if (dy > 0) // north
    {
        c1->n = 0;
        c2->s = 0;
    }
}

LM_Maze* maze_generate_with_rooms(int w, int h)
{
    LM_Maze* m = (LM_Maze*)malloc(sizeof(LM_Maze));
    if (m == NULL)
    {
        return NULL;
    }

    LM_Point p = {w, h};
    m->dimension = p;
    m->cells = NULL;

    m->num_rooms = 0;
    m->rooms = (LM_Rect*)malloc(5 * sizeof(LM_Rect));
    if (m->rooms == NULL)
    {
        free(m);
        return NULL;
    }
    m->num_rooms = 5;

    gen_clear(m);

    const int max_rooms = 5;
    int num_rooms = 0;
    int room_size = 3;
    LM_Point corner;
    LM_Point placed[5];

    int i;

    int limiter = 0;

    while (num_rooms < max_rooms)
    {
        corner.x = randint(3, m->dimension.x - room_size);
        corner.y = randint(3, m->dimension.y - room_size);
        printf("room: (%d,%d,%d,%d)\n", corner.x, corner.y, room_size, room_size);
        int ok = 1;
        for (i = 0; i < num_rooms; ++i)
        {
            LM_Rect a = { corner.x, corner.y, room_size, room_size };
            LM_Rect b = { placed[i].x, placed[i].y, room_size, room_size};
            ok = !overlap(a, b);
        }
        if (ok)
        {
            printf("place a room\n");
            limiter = 0;
            int y;
            int x;
            for (y = 0; y < room_size; ++y)
            {
                for (x = 0; x < room_size; ++x)
                {
                    LM_Point loc = {corner.x + x, corner.y + y};
                    LM_Cell* c = maze_get(m, loc.x, loc.y);
                    c->visited = 1;

                    if (y < room_size - 1)
                    {
                        //maze_remove_wall(m, loc.x, loc.y, loc.x, loc.y + 1);
                    }

                    if (x < room_size - 1)
                    {
                        //maze_remove_wall(m, loc.x, loc.y, loc.x + 1, loc.y);
                    }
                }
            }
            placed[num_rooms] = corner;
            LM_Rect* r = &m->rooms[num_rooms];
            r->x = corner.x;
            r->y = corner.y;
            r->w = room_size;
            r->h = room_size;
            num_rooms++;
        }
        limiter++;
        if (limiter > 1000)
        {
            printf("libmaze error: failed to place a single room\n");
            break;
        }
    }

    //int i;
    int j;
    printf("all visited cells\n");
    for (i = 0; i < m->dimension.y; ++i)
    {
        for (j = 0; j < m->dimension.x; ++j)
        {
            printf("%d ", maze_get(m, j, i)->visited);
        }
        printf("\n");
    }

    gen_new(m);

    return m;
}

LM_Maze* maze_generate(int w, int h)
{
    LM_Maze* m = (LM_Maze*)malloc(sizeof(LM_Maze));
    if (m == NULL)
    {
        return NULL;
    }
    
    LM_Point p = {w, h};
    m->dimension = p;
    m->cells = NULL;
    m->rooms = NULL;

    gen_new(m);

    return m;
}

LM_Grid* maze_format(LM_Maze* m, int padding)
{
    return fmt_gen(m, padding);
}

int grid_format(LM_Grid* g, int padding)
{
    return fmt_mod(g, padding);
}

int grid_space(LM_Grid* g, int spacing)
{
    return fmt_space(g, spacing);
}

int grid_fill_rooms(LM_Grid* g)
{

}

LM_Maze* maze_open(const char* fn)
{
    LM_Maze* m = (LM_Maze*)malloc(sizeof(LM_Maze));
    if (m == NULL)
    {
        return NULL;
    }

    FILE* fp = fopen(fn, "rb");
    if (!fp)
    {
        free(m);
        return NULL;
    }

    fread(&m->dimension.x, sizeof(uint8_t), 1, fp);
    fread(&m->dimension.y, sizeof(uint8_t), 1, fp);

    int buffer_size = m->dimension.x * m->dimension.y;
    uint8_t* buffer = (uint8_t*)malloc(buffer_size * sizeof(uint8_t));
    if (buffer == NULL)
    {
        return NULL;
    }
    fread(buffer, sizeof(uint8_t), buffer_size, fp);

    int i;
    for (i = 0; i < buffer_size; ++i)
    {
        uint8_t ch = buffer[i];
        LM_Cell* c = &m->cells[i];
        c->visited = 1;
        c->e = (ch >> 0) & 0x1;
        c->n = (ch >> 1) & 0x1;
        c->w = (ch >> 2) & 0x1;
        c->s = (ch >> 3) & 0x1;
    }

    free(buffer);
    fclose(fp);
    
    return m;
}

void maze_save(LM_Maze* m, const char* fn)
{
    const char E = 0x1;
    const char N = 0x2;
    const char W = 0x4;
    const char S = 0x8;

    FILE* fp = fopen(fn, "wb");

    // write header
    fwrite(&m->dimension.x, sizeof(uint8_t), 1, fp);
    fwrite(&m->dimension.y, sizeof(uint8_t), 1, fp);

    int len = m->dimension.x * m->dimension.y;
    
    int i;
    for (i = 0; i < len; ++i)
    {
        LM_Cell* c = &m->cells[i];
        uint8_t ch = 0;

        if (c->e)
        {
            ch |= E;
        }
        if (c->n)
        {
            ch |= N;
        }
        if (c->w)
        {
            ch |= W;
        }
        if (c->s)
        {
            ch |= S;
        }

        fwrite(&ch, sizeof(uint8_t), 1, fp);
    }

    fclose(fp);
}

void grid_save(LM_Grid* g, const char* fn)
{
    FILE* fp = fopen(fn, "wb");
    fclose(fp);
}

LM_Cell* maze_get(LM_Maze* m, int x, int y)
{
    if (x < 0 || y < 0 || x >= m->dimension.x || y >= m->dimension.y)
    {
        return NULL;
    }
    int index = (x % m->dimension.x) + (y * m->dimension.y);
    return &m->cells[index];
}

uint8_t grid_get(LM_Grid* g, int x, int y)
{
    int index = (x % g->dimension.x) + (y * g->dimension.y);
    return g->cells[index];
}

uint8_t* grid_getp(LM_Grid* g, int x, int y)
{
    int index = (x % g->dimension.x) + (y * g->dimension.y);
    return &g->cells[index];
}

void maze_free(LM_Maze* m)
{
    if (m != NULL)
    {
        if (m->cells != NULL)
        {
            free(m->cells);
        }
        if (m->rooms != NULL)
        {
            free(m->rooms);
        }
        free(m);
    }
}

void grid_free(LM_Grid* g)
{
    if (g != NULL)
    {
        if (g->cells != NULL)
        {
            free(g->cells);
        }
        free(g);
    }
}