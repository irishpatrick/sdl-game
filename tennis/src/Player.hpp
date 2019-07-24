#pragma once

#include <engine.hpp>

class Ball;

using namespace engine;

class Player : public Sprite
{
public:
    Player() {}
    ~Player() {}

    void init(Context&);

    void left(float);
    void right(float);
    BoundingBox getBoundingBox();
    void checkAndHit(Context&, Ball*);

protected:
    float speed = 200;
    BoundingBox hitbox;
};