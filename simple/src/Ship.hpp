#pragma once

#include <engine.hpp>

class Ship : public engine::Sprite
{
public:
    Ship();
    ~Ship();

    void draw(engine::Context& ctx);
};
