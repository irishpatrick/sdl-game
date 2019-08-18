#include "GridSprite.hpp"
#include "Grid.hpp"

GridSprite::GridSprite() :
    Sprite(),
    gridx(0),
    gridy(0),
    targx(0),
    targy(0),
    x_dir(0),
    y_dir(0),
    speed(1.5f),
    moving(0)
{

}

GridSprite::~GridSprite()
{

}

void GridSprite::setGridPos(int gx, int gy)
{
    Grid* g = (Grid*)sparent;
    x = gx * g->getSize();
    y = gy * g->getSize();
    gridx = gx;
    gridy = gy;
    targx = gx;
    targy = gy;
}

Point GridSprite::getGridPos()
{
    return Point(gridx, gridy);
}

void GridSprite::left()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx - 1, targy)) return;
    targx = gridx - 1;
    xvel = -speed;
}

void GridSprite::right()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx + 1, targy)) return;
    targx = gridx + 1;
    xvel = speed;
}

void GridSprite::up()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy - 1)) return;
    targy = gridy - 1;
    yvel = -speed;
}

void GridSprite::down()
{
    if (moving) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy + 1)) return;
    targy = gridy + 1;
    yvel = speed;
}

void GridSprite::update()
{
    Sprite::update();

    Grid* g = (Grid*)sparent;
    moving = fabs(xvel) + fabs(yvel) > 0;
    float tx = targx * g->getSize();
    float ty = targy * g->getSize();

    float dx = x - tx;
    float dy = y - ty;
    float thr = speed / 2.0f;

    if (fabs(dx) < thr)
    {
        xvel = 0;
        gridx = targx;
    }

    if (fabs(dy) < thr)
    {
        yvel = 0;
        gridy = targy;
    }
}
