#include "Ship.hpp"
#include <iostream>

Ship::Ship() : Sprite()
{
    visible = true;
    speed = 200;
    missile.setVisible(false);
}

Ship::~Ship()
{

}

void Ship::init(engine::Context& ctx)
{
    missile.init(ctx);
    missile.setTexture(engine::Assets::getTexture("missile.png"));
}

void Ship::update(float delta)
{
    Sprite::update(delta);
    missile.update(delta);
    xvel = 0;
}

void Ship::draw(engine::Context& ctx)
{
    Sprite::draw(ctx);
    missile.draw(ctx);
}

void Ship::right()
{
    xvel = speed;
}

void Ship::left()
{
    xvel = -speed;
}

void Ship::fire()
{
    if (missile.isVisible())
    {
        return;
    }
    missile.x = x + (w/2) - (missile.w / 2);
    missile.y = y;
    missile.setVisible(true);
}

Missile* Ship::getMissile()
{
    return &missile;
}
