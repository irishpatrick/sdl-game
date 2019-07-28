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

void Player::checkAndHit(BoundingBox& box, Ball* ball)
{
    if (Util::checkIntersect(getBoundingBox(), ]ball->getBoundingBox()))
    {
        /*float side = getBoundingBox().center().x - ball->getBoundingBox().center().x;
        float dx, dy;

        if (ball->y < box.h / 2)
        {
            dy = box.h - ball->y;
        }
        else if (ball->y > box.h / 2)
        {
            dy = ball->y;
        }

        if (side > 0) // left
        {
            dx = ball->x;
        }
        else if (side < 0) // right
        {
            dx = box.h - ball->x;
        }*/

        ball->bounce(box, this);
    }
}