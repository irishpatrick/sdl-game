#pragma once

#include <engine.hpp>

class Player;

using namespace engine;

class Ball : public Sprite
{
public:
    Ball() : 
        dtheta(0),
        speed(4),
        height(0.0f)
    {}
    ~Ball() {}

    void init(Context&);
    //BoundingBox getBoundingBox();
    void bounce(BoundingBox&, Player*);
    void setShadow(Context&);
    void update(Context&, float);
    void draw(Context&, float);
    void serve(Context&, Player*);

private:
    float height;
    Sprite shadow;
    float dtheta;
    float speed;
};
