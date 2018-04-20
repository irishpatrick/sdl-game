#ifndef GRIDSPRITE_H
#define GRIDSPRITE_H

#include <iostream>
#include <engine.h>

using namespace std;

class GridSprite: public engine::Sprite {
public:
    GridSprite();
    ~GridSprite();

    void init();
    void velocityUpdate(float);

    void setGridSize(int);
    void setGridPos(int, int);
    void moveTo(int, int);
    inline void setMovementSpeed(float s) {
        duration = s;
    }

    inline void left() {
        if (moving) return;
        moveTo(--gridx, gridy);
    }

    inline void right() {
        if (moving) return;
        moveTo(++gridx, gridy);
    }

    inline void up() {
        if (moving) return;
        moveTo(gridx, --gridy);
    }

    inline void down() {
        if (moving) return;
        moveTo(gridx, ++gridy);
    }

protected:
    int grid;
    float gridx;
    float gridy;

private:
    bool moving;
    float mspeed;
    float t;
    float duration;
    float tx;
    float ty;
    float sx;
    float sy;
};

#endif /* GRIDSPRITE_H */
