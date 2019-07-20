#include "Player.hpp"
#include "Ball.hpp"

void Player::init(Context& ctx)
{
    setTexture(Assets::getTexture("player.png"));
    x = ctx.getWidth() / 2 - w / 2;
    y = ctx.getHeight() - h - 0.5 * h;
    hitbox.xywh(0, 10, w, h / 2);
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

void Player::checkAndHit(Context& ctx, Ball* ball)
{
    if (Util::checkIntersect(getBoundingBox(), ball->getBoundingBox()))
    {
        float side = getBoundingBox().center().x - ball->getBoundingBox().center().x;
        float dx, dy;

        if (ball->y < ctx.getHeight() / 2)
        {
            dy = ctx.getHeight() - ball->y;
        }
        else if (ball->y > ctx.getHeight() / 2)
        {
            dy = ball->y;
        }

        if (side > 0) // left
        {
            dx = ball->x;
        }
        else if (side < 0) // right
        {
            dx = ctx.getWidth() - ball->x;
        }

        ball->bounce(this);
    }
}