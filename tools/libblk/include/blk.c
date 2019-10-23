#include "blk.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BLK* blk_new(int w, int h)
{
    BLK* out = (BLK*)malloc(sizeof(BLK));
    out->dimension.x = w;
    out->dimension.y = h;
    out->grid = (char*)malloc(w * h * sizeof(char));
    return 0;
}
