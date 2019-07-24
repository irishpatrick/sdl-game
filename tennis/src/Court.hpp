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
    {}

    void init(Context&);
    int judge(Ball*);
    virtual void update(Context&, float);
    void contain(Player*);

private:
    BoundingBox in_bounds;
};