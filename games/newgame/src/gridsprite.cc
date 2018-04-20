#include "gridsprite.h"

float lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

GridSprite::GridSprite(): engine::Sprite() {
    grid = 0;
    t = 0;
    tx = 0.0;
    ty = 0.0;
    duration = 0.0;
    moving = false;
    gridx = 0;
    gridy = 0;
}

GridSprite::~GridSprite() {

}

void GridSprite::velocityUpdate(float delta) {
    if (moving) {
        t += delta / duration;

        double xtx = abs(x-tx);
        double yty = abs(y-ty);
        double tolerance = 0.3;
        //cout << xtx << ", " << yty << endl;
        if (xtx < tolerance && yty < tolerance) {
            //cout << "tolerance: moving set to false" << endl;
            moving = false;
            setGridPos(tx/grid, ty/grid);
        }

        else if (t > 1.0) {
            //cout << "time: moving set to false" << endl;
            moving = false;
            setGridPos(tx/grid,ty/grid);
        }
        else {
            //cout << "t: " << t << endl;
            x = lerp(sx, tx, t);
            y = lerp(sy, ty, t);
        }
    }
}

void GridSprite::setGridSize(int g) {
    grid = g;
}

void GridSprite::setGridPos(int gx, int gy) {
    gridx = gx;
    gridy = gy;
    x = gx * grid;
    y = gy * grid;
}

void GridSprite::moveTo(int gx, int gy) {
    if (!moving) {
        moving = true;
        sx = x;
        sy = y;
        tx = gx * grid;
        ty = gy * grid;
        t = 0;
    }
}
