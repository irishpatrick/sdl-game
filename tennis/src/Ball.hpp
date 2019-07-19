#pragma once

#include <engine.hpp>

using namespace engine;

class Ball : public Sprite
{
public:
    Ball() {}
    ~Ball() {}

    void init(Context&);
    BoundingBox getBoundingBox();
    void bounce();
    void update(float);
    void draw(Context&);

private:
    Sprite shadow;
};