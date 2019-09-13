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

void Hud::setPlayer(Player* p)
{
    player = p;
}