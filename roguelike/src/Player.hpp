#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"
#include "Item.hpp"
#include <vector>
#include "Stats.hpp"

using namespace engine;

class Player : public GridSprite
{
public:
    Player();
    ~Player();

    virtual void give(Item);
    virtual void use(Item);
    std::vector<Item>& getInventory();
    Stats getStats();

private:
    Item* weapon;
    Item* armor;
    std::vector<Item> inventory;
    Stats stats;
};
