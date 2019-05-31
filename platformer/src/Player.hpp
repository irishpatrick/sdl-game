#pragma once

#include <engine.hpp>

class Player : public engine::Sprite
{
public:
    Player() : Sprite()
    {
        jump_clk = 0.0f;
        jump_ready = true;
        on_ground = false;
    }
    ~Player() {}

    void jump(float);
    void move(float);
    void update(float);

private:
    float jump_clk;
    bool jump_ready;
    bool on_ground;
};