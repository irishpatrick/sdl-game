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

void Ball::bounce(Player* player)
{
    float glance = ((x + w / 2) - (player->x + player->w / 2)) / (player->w / 2 + w / 2);
    std::cout << "glance=" << glance << std::endl;
    yvel = yvel * -1.0f;
    dtheta = Random::randint(-200, 200);
}

void Ball::serve(Context& ctx, int side)
{
    x = ctx.getWidth() / 2;
    if (side == 0)
    {
        yvel = -100.0f;
        y = ctx.getHeight() * (2.0f / 3.0f);
    }
    else if (side == 1)
    {
        yvel = 100.0f;
        y = ctx.getHeight() * (1.0f / 3.0f);
    }
}

void Ball::update(float delta)
{
    x += xvel * delta;
    y += yvel * delta;
    theta += dtheta * delta;
}

void Ball::draw(Context& ctx)
{
    shadow.draw(ctx);
    Sprite::draw(ctx);
}
