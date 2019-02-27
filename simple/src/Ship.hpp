#pragma once

#include <engine.hpp>
#include "Missile.hpp"

class Ship : public engine::Sprite
{
public:
    Ship();
    ~Ship();

    void left();
    void right();
    void fire();

    void init(engine::Context&);
    void update(float delta);
    void draw(engine::Context&);

    Missile* getMissile();

private:
    Missile missile;
    float speed;
};
