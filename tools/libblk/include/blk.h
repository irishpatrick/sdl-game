#ifndef BLK_H
#define BLK_H

#include <stdint.h>

#ifdef __cplusplus  
extern "C" {
#endif
    typedef struct _BLKPoint
    {
        int x;
        int y;
    } BLKPoint;

    typedef struct _BLK
    {
        BLKPoint dimension;
        int entries;
        char table[255][255];
        uint8_t* grid;
    } BLK;

    BLK* blk_new(int, int);
    BLK* blk_open(const char*);
    int blk_add_entry(BLK*, const char*, uint8_t);
    const char* blk_get_entry(BLK*, uint8_t);
    uint8_t blk_at(BLK*, int, int);
    int blk_set(BLK*, int, int, uint8_t);
    int blk_save(BLK*, const char*);
    int blk_free(BLK*);
    

#ifdef __cplusplus  
}
#endif

#endif BLK_H