#include "Player.hpp"
#include <cmath>
#include <iostream>

void Player::jump(float delta)
{
    float rate = 5.0f;
    float initial = 1.5f;

    bool jumping = !((collision_faces >> 2) & 0x01);

    std::cout << jumping << " ";

    if (jumping)
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

void Player::update(float delta)
{

    Sprite::update(delta);
}
