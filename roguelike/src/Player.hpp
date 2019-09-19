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

    void setName(const std::string&);
    std::string getName();

    virtual void give(Item);
    virtual void use(Item);
    virtual void equip(const std::string&);
    std::vector<Item>& getInventory();
    Stats getStats();
    Item* getWeapon();

    bool canMove();

    void attack();
    void hit(Player*);

    void update();
    void draw(Context&, float);

private:
    Item* weapon;
    Item* armor;
    std::vector<Item> inventory;
    Stats stats;
    std::string name;
    bool attacking;
    int attackCounter;
};
