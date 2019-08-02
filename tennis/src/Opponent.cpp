#include "Opponent.hpp"
#include "Ball.hpp"
#include "Random.hpp"

void Opponent::init(Context& ctx)
{
    setTexture(Assets::getTexture("cat2.png"));
    w = 64;
    h = 64;
    x = ctx.getWidth() / 2 - w / 2;
    y = 0.5 * h;
    hitbox.xywh(0, h / 2 - 10, w, h / 2);
    target = x;
}

void Opponent::calculate(Ball* b)
{
    Point p1(b->x, b->y);
    Point p2(b->x + b->xvel, b->y + b->yvel);
    Line ln;
    ln.fit(p1, p2);

    target = ln.solveInverse(y);
    target -= w / 2;
    target += Random::randint(-w / 3, w / 3);
}

void Opponent::process(Ball* b)
{
    if (!b->IsVisible())
    {
        dir = 0;
        return;
    }
    
    if (fabs(x - target) < 10)
    {
    }
    else if (x > target)
    {
        dir = -1;
    }
    else if (x < target)
    {
        dir = 1;
    }
    else
    {
        dir = 0;
    }
}

/*int Opponent::checkAndHit(BoundingBox& box, Ball* b)
{
    int val = Player::checkAndHit(box, b);
    if (val)
    {
        calculate(b);
    }
    return val;
}*/
