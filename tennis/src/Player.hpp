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

    void left();
    void right();
    void update() override;
    BoundingBox getBoundingBox();
    BoundingBox getRelativeBoundingBox();
    virtual int checkAndHit(BoundingBox&, Ball*);

protected:
    float speed = 2.2;
    int dir = 0;
    BoundingBox hitbox;
};