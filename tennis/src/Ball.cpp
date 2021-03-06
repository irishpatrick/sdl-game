#include <iostream>
#include "Ball.hpp"
#include "Random.hpp"
#include "Player.hpp"

void Ball::init(Context& ctx)
{
    visible = false;
    x = -100;
    y = -100;
    setTexture(Assets::getTexture("ball.png"));
    shadow.init(ctx);
    shadow.setTexture(Assets::getTexture("ball_shadow.png"));
    setBoundingBox(w / 4, h / 4, w / 2, h / 2);
}

void Ball::bounce(BoundingBox& box, Player* player)
{
    float cx = box.x + box.w / 2;
    float cy = box.y + box.h / 2;
    float mx = box.x + box.w;
    float my = box.y + box.h;
    if (player->y < cy)
    {
        y = player->getBoundingBox().y + player->getBoundingBox().h;
    }
    else
    {
        y = player->getBoundingBox().y - h;
    }
    float glance = ((x + w / 2) - (player->x + player->w / 2)) / (player->w / 2 + w / 2);
    float phi_max = 0;
    float dx = 0.0f;
    float dy = 1.0f;
    if (y < cy)
    {
        dy = my - y;
    }
    else if (y > cy)
    {
        dy = y;
    }
    if (glance > 0)
    {
        dx = mx - x;
        phi_max = atanf(dx / dy);
    }
    else if (glance < 0)
    {
        dx = x;
        phi_max = atanf(dx / dy);
    }

    xvel = speed * sinf(phi_max * glance);
    yvel = -1.0f * (yvel / fabsf(yvel)) * speed * cosf(phi_max * glance);

    dtheta = Random::randint(-3, 3);
}

void Ball::serve(Context& ctx, Player* p)
{
    visible = true;
    xvel = 0;
    xvel = 0;

    if (p->y > ctx.getHeight() / 2)
    {
        yvel = -speed;
        y = p->y - h;
    }
    else if (p->y < ctx.getHeight() / 2)
    {
        yvel = speed;
        y = p->y + p->h;
    }

    x = p->x + w;
}

void Ball::setShadow(Context& ctx)
{
    if (yvel < 0)
    {
        height = 10 * fabsf(y - ctx.getHeight() * (1.0f / 4.0f));
    }
    else if (yvel > 0)
    {
        height = 10 * fabsf(y - ctx.getHeight() * (3.0f / 4.0f));
    }
    //height = fminf(height, 10000);
}

void Ball::update(Context& ctx)
{
    visible = Util::checkIntersect(getBoundingBox(), ctx.getBoundingBox());
    shadow.setVisible(visible);
    if (!visible)
    {
        xvel = 0;
        yvel = 0;
    }

    x += xvel;
    y += yvel;
    theta += dtheta;
    shadow.x = x + (sqrtf(height)) / 2;
    shadow.y = y + (sqrtf(height)) / 2;
    shadow.yvel = yvel; // kind of a hack
}

void Ball::draw(Context& ctx, float e)
{
    shadow.draw(ctx, e);
    Sprite::draw(ctx, e);
}
