#include "Player.hpp"

Player::Player() : Sprite()
{
    x_dir = 0;
    y_dir = 0;
}

Player::~Player()
{

}

void Player::translateX(float val)
{
    if (val != 0)
    {
        Sprite::translateX(val);
        x_dir = val / fabsf(val);
        y_dir = 0;
    }
}

void Player::translateY(float val)
{
    if (val != 0)
    {
        Sprite::translateY(val);
        y_dir = val / fabsf(val);
        x_dir = 0;
    }
}

void Player::attack(Group& group)
{

}
