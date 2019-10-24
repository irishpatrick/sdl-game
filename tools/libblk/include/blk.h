#ifndef BLK_H
#define BLK_H

#include <stdint.h>

#ifdef __cplusplus  
extern "C" {
#endif
    typedef struct _Point
    {
        int x;
        int y;
    } Point;

    typedef struct _BLK
    {
        Point dimension;
        int entries;
        char table[255][255];
        uint8_t* grid;
    } BLK;

    BLK* blk_new(int, int);
    BLK* blk_open(const char*);
    int blk_save(BLK*, const char*);
    int blk_free(BLK*);
    

#ifdef __cplusplus  
}
#endif

#endif BLK_H