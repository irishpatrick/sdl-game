#pragma once

#include <engine.hpp>

using namespace engine;

class Grid;

class GridSprite : public Sprite
{
public:
    GridSprite();
    ~GridSprite();

    void setGridPos(int, int);
    Point getGridPos();
    void left();
    void right();
    void up();
    void down();

    virtual void interact(GridSprite*);
    virtual void prompt();
    virtual void update();
    virtual void strafe();

    Grid* getGridParent();

private:
    int strafing;
    int gridx;
    int gridy;
    int targx;
    int targy;
    int x_dir;
    int y_dir;
    float speed;
    int moving;
    Point dir;
};
