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
    Point getDir();
    void left();
    void right();
    void up();
    void down();

    virtual bool canMove();
    virtual bool canMove(int, int);
    virtual void interact(GridSprite*);
    virtual void prompt();
    virtual void update();
    virtual void strafe();

    void setSolid(bool);
    bool isSolid();

    void setObeyWalls(bool);
    bool obeysWalls();

    Grid* getGridParent();

protected:
    Point dir;
    int gridx;
    int gridy;

private:
    bool solid;
    bool obeyWalls;
    int strafing;
    int targx;
    int targy;
    int x_dir;
    int y_dir;
    float speed;
    int moving;
};
