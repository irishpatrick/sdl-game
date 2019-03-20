#pragma once
#include <stdint.h>

typedef struct _Box
{
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} Box;

int box_collision(Box*, Box*);