#pragma once

#include <engine.hpp>

class Player : public engine::Sprite
{
public:
    Player() : Sprite()
    {
        jump_clk = 0.0f;
        jump_ready = true;
    }
    ~Player() {}

    void jump(float);
    void update(float);

private:
    float jump_clk;
    bool jump_ready;
};