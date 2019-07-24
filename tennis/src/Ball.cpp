#include <iostream>
#include "Ball.hpp"
#include "Random.hpp"
#include "Player.hpp"

void Ball::init(Context& ctx)
{
    setTexture(Assets::getTexture("ball.png"));
    shadow.init(ctx);
    shadow.setTexture(Assets::getTexture("ball_shadow.png"));
}

BoundingBox Ball::getBoundingBox()
{
    return BoundingBox(x, y, w, h);
}

void Ball::bounce(Context& ctx, Player* player)
{
    if (player->y < ctx.getWidth() / 2)
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
    if (y < ctx.getHeight() / 2)
    {
        dy = ctx.getHeight() - y;
    }
    else if (y > ctx.getHeight() / 2)
    {
        dy = y;
    }
    if (glance > 0)
    {
        dx = ctx.getWidth() - x;
        phi_max = atanf(dx / dy);
    }
    else if (glance < 0)
    {
        dx = x;
        phi_max = atanf(dx / dy);
    }

    xvel = speed * sinf(phi_max * glance);
    yvel = -1.0f * (yvel / fabsf(yvel)) * speed * cosf(phi_max * glance);
    
    dtheta = Random::randint(-20, 20) * 10;
}

void Ball::serve(Context& ctx, int side)
{
    visible = true;
    xvel = 0;
    x = ctx.getWidth() / 2;
    xvel = 0;
    if (side == 0)
    {
        yvel = -speed;
        y = ctx.getHeight() * (2.0f / 3.0f);
    }
    else if (side == 1)
    {
        yvel = speed;
        y = ctx.getHeight() * (1.0f / 3.0f);
    }
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
    height = fminf(height, 6000);
}

void Ball::update(Context& ctx, float delta)
{   
    //std::cout << ctx.getBoundingBox() << "\t|\t" << getBoundingBox() << std::endl;
    visible = Util::checkIntersect(getBoundingBox(), BoundingBox(0, 0, ctx.getWidth(), ctx.getHeight()));
    //std::cout << "visible = " << visible << std::endl;
    shadow.setVisible(visible);
    if (!visible)
    {
        xvel = 0;
        yvel = 0;
    }

    x += xvel * delta;
    y += yvel * delta;
    theta += dtheta * delta;

    shadow.x = x + (sqrtf(height)) / 2;
    shadow.y = y + (sqrtf(height)) / 2;
}

void Ball::draw(Context& ctx)
{
    shadow.draw(ctx);
    Sprite::draw(ctx);
}
