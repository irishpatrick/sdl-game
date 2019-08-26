#pragma once

#include <engine.hpp>

using namespace engine;

class GridAlign
{
public:
    virtual void setGridPos(int, int) = 0;
    virtual Point getGridPos() = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void up() = 0;
    virtual void down() = 0;

    virtual void interact(GridAlign*) = 0;
    virtual void prompt() = 0;
};
