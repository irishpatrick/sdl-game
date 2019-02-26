#include "Ship.hpp"

Ship::Ship() : Sprite()
{
    visible = true;
}

Ship::~Ship()
{

}

void Ship::draw(engine::Context& ctx)
{
    Sprite::draw(ctx);
}
