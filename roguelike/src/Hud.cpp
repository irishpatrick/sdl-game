#include "Hud.hpp"
#include "Player.hpp"
#include <iostream>

Hud::Hud() :
    Sprite(),
    player(nullptr)
{

}

Hud::~Hud()
{

}

void Hud::init()
{
    Context& ctx = MyEngine::getContext();

    heart.init(ctx);
    heart.setTexture(Assets::getTexture("health.png"));
}

void Hud::setPlayer(Player* p)
{
    player = p;
}

void Hud::draw()
{
    Context& ctx = MyEngine::getContext();
}
