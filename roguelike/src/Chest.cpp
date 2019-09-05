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
    setCurrentAnimation("closed");
    playAnimation();
    w = 32;
    h = 32;
}

void Chest::interact(GridSprite* prompt)
{
    if (searched) return;
    setCurrentAnimation("open");
    playAnimation();
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
    int n = Random::randint(3, 8);
    Item food;
    Item weapon;
    food.load("assets/items/apple.json");
    food.setQuantity(n);
    weapon.load("assets/items/frying_pan.json");
    weapon.setQuantity(1);
    contents.push_back(food);
    contents.push_back(weapon);
}
