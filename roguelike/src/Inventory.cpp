#include "Inventory.hpp"
#include "Player.hpp"
#include <iostream>

Inventory::Inventory() :
    State()
{
    setName("inventory");
}

Inventory::~Inventory()
{
    
}

void Inventory::init()
{
    //Context& ctx = MyEngine::getContext();
}

void Inventory::fill(Player* p)
{
    player = p;
}

void Inventory::update()
{
    Keyboard::poll();
    if (Keyboard::isPressed("escape"))
    {
        MyEngine::setCurrentState("dungeon");
    }
}

void Inventory::render(float ex)
{
    //std::cout << "draw inventory" << std::endl;
    if (player == nullptr)
    {
        //std::cout << "player null, cannot draw" << std::endl;
        return;
    }
    int n = 0;
    int p = 10;
    int w = 32;
    for (auto& e : player->getInventory())
    {
        Texture* t = e.getTexture();
        if (t == nullptr)
        {
            //std::cout << "null texture, cannot display" << std::endl;
            continue;
        }
        t->display(p + w * n, p);
        ++n;
    }
}