#include "Player.hpp"
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
