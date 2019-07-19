#include "Ball.hpp"

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

void Ball::bounce()
{

}

void Ball::update(float delta)
{

}

void Ball::draw(Context& ctx)
{
    shadow.draw(ctx);
    Sprite::draw(ctx);
}
