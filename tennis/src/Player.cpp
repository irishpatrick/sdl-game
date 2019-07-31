#include "Player.hpp"
#include "Ball.hpp"

void Player::init(Context& ctx)
{
    setTexture(Assets::getTexture("player.png"));
    x = ctx.getWidth() / 2 - w / 2;
    y = ctx.getHeight() - h - 1.5 * h;
    hitbox.xywh(w / 8, 10, 6 * w / 8, h / 2);
}

void Player::left(float delta)
{
    translateX(-speed * delta);
}

void Player::right(float delta)
{
    translateX(speed * delta);
}

BoundingBox Player::getBoundingBox()
{
    return BoundingBox(x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h);
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