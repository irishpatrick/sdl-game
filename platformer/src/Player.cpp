#include "Player.hpp"
#include <cmath>
#include <iostream>

void Player::jump(float delta)
{
    float rate = 5.0f;
    float initial = 1.5f;

    if (!on_ground)
    {
        float e = (logf(initial) / logf(rate)) - jump_clk;
        yvel += -1.0f * powf(rate, e);
        jump_clk += delta;
    }
    else
    {
        jump_clk = 0.0f;
        yvel = -1.0f * initial;
    }
}

void Player::move(float velocity)
{
    if (on_ground)
    {
        xvel = velocity;
    }
    else
    {
        xvel += (velocity / (abs(velocity) + 0.0001f)) * (1.0f / (30 * (abs(xvel) + 1.0f)));
    }
}

void Player::update(float delta)
{
    on_ground = ((collision_faces >> 2) & 0x01);
    Sprite::update(delta);
}
