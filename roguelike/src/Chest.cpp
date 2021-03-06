#include "Chest.hpp"
#include "Player.hpp"
#include "Textbox.hpp"
#include <iostream>

Chest::Chest() :
    GridSprite(),
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

    Textbox::reset();
    Textbox::fillDialogue("you found some shit!\nNow get lost.");
    Textbox::play();
}

void Chest::fill()
{
    int n = Random::randint(3, 8);
    Item food;
    Item weapon;
    Item sw;
    food = Item::get("apple");
    food.setQuantity(n);
    weapon = Item::get("frying pan");
    weapon.setQuantity(1);
    sw = Item::get("sword");
    sw.setQuantity(1);
    contents.push_back(food);
    contents.push_back(weapon);
    contents.push_back(sw);
}
