#include "Chest.hpp"
#include <iostream>

Chest::Chest() :
    searched(false)
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
    if (searched) return;
    std::cout << "chest" << std::endl;
    searched = true;
    contents.clear();
}

void Chest::fill()
{
    int n = Random::randint(1, 8);
    int i;
    for (i = 0; i < n; ++i)
    {
        
    }
}
