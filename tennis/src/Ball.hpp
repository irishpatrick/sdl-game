#pragma once

#include <engine.hpp>

class Player;

using namespace engine;

class Ball : public Sprite
{
public:
    Ball() : 
        dtheta(0),
        speed(400),
        height(0.0f)
    {}
    ~Ball() {}

    void init(Context&);
    BoundingBox getBoundingBox();
    void bounce(Context&, Player*);
    void setShadow(Context&);
    void update(float);
    void draw(Context&);
    void serve(Context&, int);

private:
    float height;
    Sprite shadow;
    float dtheta;
    float speed;
};