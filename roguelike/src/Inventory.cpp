#include "Inventory.hpp"

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

void Inventory::update()
{
    Keyboard::poll();
    if (Keyboard::isPressed("escape"))
    {
        MyEngine::setCurrentState("dungeon");
    }
}

void Inventory::draw(float ex)
{
    //Context& ctx = MyEngine::getContext();
}