#include "GridSprite.hpp"
#include "Grid.hpp"

GridSprite::GridSprite() :
    Sprite(),
    solid(true),
    strafing(0),
    gridx(0),
    gridy(0),
    targx(0),
    targy(0),
    x_dir(0),
    y_dir(0),
    speed(1.5f),
    moving(0),
    dir(0, 1)
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

Point GridSprite::getDir()
{
    return dir;
}

bool GridSprite::canMove()
{
    return !moving;
}

void GridSprite::left()
{
    if (!strafing)
    {
        dir.x = -1;
        dir.y = 0;
    }
    if (!canMove()) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx - 1, targy)) return;
    targx = gridx - 1;
    xvel = -speed;
}

void GridSprite::right()
{
    if (!strafing)
    {
        dir.x = 1;
        dir.y = 0;
    }
    if (!canMove()) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx + 1, targy)) return;
    targx = gridx + 1;
    xvel = speed;
}

void GridSprite::up()
{
    if (!strafing)
    {
        dir.x = 0;
        dir.y = -1;
    }
    if (!canMove()) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy - 1)) return;
    targy = gridy - 1;
    yvel = -speed;
}

void GridSprite::down()
{
    if (!strafing)
    {
        dir.x = 0;
        dir.y = 1;
    }
    if (!canMove()) return;
    Grid* g = (Grid*)sparent;
    if (!g->checkMove(targx, targy + 1)) return;
    targy = gridy + 1;
    yvel = speed;
}

void GridSprite::strafe()
{
    strafing = 1;
}

void GridSprite::interact(GridSprite* prompt)
{

}

void GridSprite::prompt()
{
    Grid* g = (Grid*)sparent;
    GridSprite* at = g->at(gridx + dir.x, gridy + dir.y);
    if (at != nullptr)
    {
        at->interact(this);
    }
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

    strafing = 0;
}

Grid* GridSprite::getGridParent()
{
    Grid* out = nullptr;
    if (parent != nullptr)
    {
        out = dynamic_cast<Grid*>(parent);
    }

    return out;
}

void GridSprite::setSolid(bool val)
{
    solid = val;
}

bool GridSprite::isSolid()
{
    return solid;
}
