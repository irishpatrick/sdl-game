#include "Chest.hpp"
#include <iostream>

Chest::Chest()
{

}

Chest::~Chest()
{

}

void Chest::init(Context& ctx)
{
    setTexture(Assets::getTexture("chest.png"));
}

void Chest::interact(GridSprite* prompt)
{
    std::cout << "chest" << std::endl;
}
