#include "Opponent.hpp"
#include "Ball.hpp"

void Opponent::init(Context& ctx)
{
    setTexture(Assets::getTexture("opponent.png"));
    x = ctx.getWidth() / 2 - w / 2;
    y = 0.5 * h;
    hitbox.xywh(0, h / 2 - 10, w, h / 2);
}

void Opponent::process(Ball* b)
{
    if (b->x < x)
    {
        dir = -1;
    }
    else if (b->x > x)
    {
        dir = 1;
    }
    else
    {
        dir = 0;
    }
}

void Opponent::update(float delta)
{
    if (dir == 0)
    {

    }
    else if (dir == -1)
    {
        left(delta);
    }
    else if (dir == 1)
    {
        right(delta);
    }
    Sprite::update(delta);
}