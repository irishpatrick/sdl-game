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
    speed(1.0f),
    moving(0)
{

}

Player::~Player()
{

}

void Player::setGridPos(int gx, int gy)
{
    Grid* g = (Grid*)sparent;
    x = gx * g->getSize();
    y = gy * g->getSize();
    gridx = gx;
    gridy = gy;
    targx = gx;
    targy = gy;
}

void Player::left()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx - 1, targy)) return;
    targx = gridx - 1;
    xvel = -speed;
}

void Player::right()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx + 1, targy)) return;
    targx = gridx + 1;
    xvel = speed;
}

void Player::up()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy - 1)) return;
    targy = gridy - 1;
    yvel = -speed;
}

void Player::down()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy + 1)) return;
    targy = gridy + 1;
    yvel = speed;
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
