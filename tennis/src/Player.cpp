#include "Player.hpp"
#include "Ball.hpp"

void Player::init(Context& ctx)
{
    setTexture(Assets::getTexture("cat1.png"));
    w = 64;
    h = 64;
    x = ctx.getWidth() / 2 - w / 2;
    y = ctx.getHeight() - h - 1.5 * h;
    hitbox.xywh(w / 8, 10, 6 * w / 8, h / 2);
}

void Player::left()
{
    dir = -1;
}

void Player::right()
{
    dir = 1;
}

void Player::update()
{
    if (dir == 0)
    {
        xvel = 0;
    }
    else if (dir < 0)
    {
        xvel = -speed;
    }
    else if (dir > 0)
    {
        xvel = speed;
    }

    Sprite::update();

    dir = 0;
}

BoundingBox Player::getBoundingBox()
{
    return BoundingBox(x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h);
}

BoundingBox Player::getRelativeBoundingBox()
{
    return hitbox;
}

int Player::checkAndHit(BoundingBox& box, Ball* ball)
{
    if (Util::checkIntersect(getBoundingBox(), ball->getBoundingBox()))
    {
        ball->bounce(box, this);
        return 1;
    }
    return 0;
}
