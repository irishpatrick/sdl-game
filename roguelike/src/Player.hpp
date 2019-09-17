#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"
#include "Item.hpp"
#include "Stats.hpp"
#include <vector>
#include <string>

using namespace engine;

class Player : public GridSprite
{
public:
    Player();
    ~Player();

    virtual void give(Item);
    virtual void use(Item);
    virtual void equip(const std::string&);
    std::vector<Item>& getInventory();
    Stats getStats();
    Item* getWeapon();

    void attack();
    void hit(Player*);

private:
    Item* weapon;
    Item* armor;
    std::vector<Item> inventory;
    Stats stats;
};
