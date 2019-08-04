#pragma once

#include <engine.hpp>

using namespace engine;

class Ball;
class Player;

class Court : public Sprite
{
public:
    Court()
    {}

    ~Court()
    {
        delete texture;
    }

    void init(Context&);
    int judge(Ball*);
    virtual void update(Context&);
    void contain(Player*);
    BoundingBox& getBounds();

private:
    BoundingBox in_bounds;
};
