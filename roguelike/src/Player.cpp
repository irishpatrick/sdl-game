#include "Player.hpp"
#include "Grid.hpp"

Player::Player() :
    Sprite(),
    gridx(0),
    gridy(0),
    targx(0),
    targy(0),
    x_dir(0),
    y_dir(0),
    speed(1),
    moving(0)
{

}

Player::~Player()
{

}

void Player::setGridPos(int gx, int gy)
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    x = gx * g->getSize();
    y = gy * g->getSize();
    gridx = gx;
    gridy = gy;
}

void Player::left()
{
    if (moving) return;
    xvel = -speed;
    targx = gridx - 1;
}

void Player::right()
{
    if (moving) return;
    xvel = speed;
    targx = gridx + 1;
}

void Player::up()
{
    if (moving) return;
    yvel = -speed;
    targy = gridy - 1;
}

void Player::down()
{
    if (moving) return;
    yvel = speed;
    targy = gridy + 1;
}

void Player::update()
{
    Sprite::update();

    Grid* g = (Grid*)sparent;
    moving = fabs(xvel) + fabs(yvel) > 0;
    float tx = targx * g->getSize();
    float ty = targy * g->getSize();

    if (fabs(x - tx) == 0)
    {
        xvel = 0;
        gridx = targx;
    }

    if (fabs(y - ty) == 0)
    {
        yvel = 0;
        gridy = targy;
    }
}
