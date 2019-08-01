#include "Player.hpp"
#include <cmath>
#include <iostream>

void Player::jump(float delta)
{
    float a = 0.5f;

    if (!on_ground)
    {
        yvel += -1.0f * (a * jump_clk * jump_clk) / (0.5413f * expf(jump_clk));
        jump_clk += delta;
    }
    else
    {
        jump_clk = 0.0f;
        yvel = -1.0f;
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
