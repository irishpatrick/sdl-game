#include "Chest.hpp"
#include "Player.hpp"
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
    loadAnimation("assets/animations/chest.json");
}

void Chest::interact(GridSprite* prompt)
{
    if (searched) return;
    std::cout << "chest" << std::endl;
    searched = true;
    Player* player = dynamic_cast<Player*>(prompt);
    if (player)
    {
        for (auto& e : contents)
        {
            player->give(e);
        }
    }
    contents.clear();
}

void Chest::fill()
{
    int n = Random::randint(1, 8);
    int i;
    for (i = 0; i < n; ++i)
    {
        Item item;
        item.load("assets/items/apple.json");
        contents.push_back(item);
    }
}
