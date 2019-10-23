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
        char** table;
        uint8_t* grid;
    } BLK;

    BLK* blk_new(int, int);
    BLK* blk_open(const char*);
    int blk_save(BLK*, const char*);
    int blk_close(BLK*);
    

#ifdef __cplusplus  
}
#endif

#endif BLK_H