#include "blk.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "util.h"

BLK* blk_new(int w, int h)
{
    BLK* out = (BLK*)malloc(sizeof(BLK));
    if (out == NULL)
    {
        return NULL;
    }
    out->dimension.x = w;
    out->dimension.y = h;
    out->entries = 0;
    memset(out->table, 0, 255 * 255 * sizeof(char));
    out->grid = (uint8_t*)malloc(w * h * sizeof(uint8_t));
    if (out->grid == NULL)
    {
        free(out);
        return NULL;
    }
    memset(out->grid, 0, w * h * sizeof(char));
    return out;
}

int blk_add_entry(BLK* b, const char* tag, uint8_t value)
{
    b->entries += 1;
    int len = (int)fmin(strlen(tag), 255);
    strncpy(b->table[value], tag, len);
    return 0;
}

const char* blk_get_entry(BLK* b, uint8_t index)
{
    return b->table[index];
}

uint8_t blk_at(BLK* b, int x, int y)
{
    if (x < 0 || x > b->dimension.x || y < 0 || y > b->dimension.y)
    {
        return 0;
    }
    return b->grid[get_index(b, x, y)];
}

int blk_set(BLK* b, int x, int y, uint8_t value)
{
    if (b == NULL ||
        x < 0 || x > b->dimension.x ||
        y < 0 || y > b->dimension.y)
    {
        return 1;
    }
    b->grid[get_index(b, x, y)] = value;
    return 0;
}

BLK* blk_open(const char* fn)
{
    FILE* fp = fopen(fn, "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    char magic[4];
    fread(magic, sizeof(char), 3, fp);
    magic[3] = '\0';
    if (strcmp(magic, "BLK") != 0)
    {
        fclose(fp);
        return NULL;
    }

    int dimensions[2];
    memset(dimensions, 0, 2 * sizeof(int));
    fread(dimensions, sizeof(int), 2, fp);
    if (dimensions[0] <= 0 || dimensions[1] <= 0)
    {
        fclose(fp);
        return NULL;
    }
    BLK* b = blk_new(dimensions[0], dimensions[1]);
    if (b == NULL)
    {
        fclose(fp);
        return NULL;
    }

    fread(&b->entries, 1, sizeof(int), fp);
    int i;
    for (i = 0; i < b->entries; i++)
    {
        char* str = b->table[i];
        char c = '\0';
        do
        {
            fread(&c, sizeof(char), 1, fp);
            int cur_len = strlen(str);
            str[cur_len] = c;
            str[cur_len + 1] = '\0';
        } while (c != '\0');
    }

    fread(b->grid, dimensions[0] * dimensions[1], sizeof(uint8_t), fp);

    return b;
}

int blk_save(BLK* b, const char* fn)
{
    FILE* fp = fopen(fn, "wb");
    if (fp == NULL)
    {
        return 1;
    }

    const char magic[4] = "BLK";
    fwrite(magic, sizeof(char), 3, fp);

    int dimension[2];
    dimension[0] = b->dimension.x;
    dimension[1] = b->dimension.y;
    fwrite(dimension, sizeof(int), 2, fp);

    fwrite(&b->entries, sizeof(int), 1, fp);
    int i;
    for (i = 0; i < b->entries; i++)
    {
        fwrite(b->table[i], sizeof(char), strlen(b->table[i]), fp);
    }

    fwrite(b->grid, sizeof(uint8_t), dimension[0] * dimension[1], fp);

    fclose(fp);
    return 0;
}

int blk_free(BLK* b)
{
    if (b->grid != NULL)
    {
        free(b->grid);
    }
    if (b != NULL)
    {
        free(b);
    }

    return 0;
}
