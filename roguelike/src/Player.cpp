#include "Player.hpp"
#include "Grid.hpp"
#include <iostream>

Player::Player() :
    weapon(nullptr),
    armor(nullptr),
    stats()
{

}

Player::~Player()
{

}

void Player::setName(const std::string& str)
{
    name = str;
}

std::string Player::getName()
{
    return name;
}

void Player::update()
{
    GridSprite::update();
    
    if (stats.getHp() <= 0)
    {
        setVisible(false);
    }
}

void Player::give(Item item)
{
    std::cout << "received " << item.getQuantity() << " " << item.getName() << "(s)" << std::endl;
    inventory.push_back(item);
}

void Player::use(Item item)
{
    const std::string type = item.getType();
    if (type == "food")
    {

    }
}

std::vector<Item>& Player::getInventory()
{
    return inventory;
}

Stats Player::getStats()
{
    return stats;
}

void Player::equip(const std::string& name)
{
    for (auto& e : inventory)
    {
        if (e.getName() == name)
        {
            if (e.getType() == "weapon")
            {
                weapon = &e;
            }
            else if (e.getType() == "armor")
            {
                armor = &e;
            }
        }
    }
}

Item* Player::getWeapon()
{
    return weapon;
}

void Player::attack()
{
    Grid* g = (Grid*)sparent;
    if (g == nullptr)
    {
        return;
    }
    GridSprite* at = g->at(gridx + dir.x, gridy + dir.y);
    if (at == nullptr)
    {
        return;
    }

    Player* p = nullptr;
    p = dynamic_cast<Player*>(at);
    if (p == nullptr)
    {
        return;
    }

    p->hit(this);
}

void Player::hit(Player* other)
{
    std::cout << name << " hit by " << other->getName() << std::endl;
    Item* w = other->getWeapon();
    if (w == nullptr)
    {
        return;
    }
    stats.modHp(-1 * w->getDataPoint(0));
}
