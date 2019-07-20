#pragma once

#include <engine.hpp>

class Player;

using namespace engine;

class Ball : public Sprite
{
public:
    Ball() : dtheta(0) {}
    ~Ball() {}

    void init(Context&);
    BoundingBox getBoundingBox();
    void bounce(Player*);
    void update(float);
    void draw(Context&);
    void serve(Context&, int);

private:
    Sprite shadow;
    float dtheta;
};