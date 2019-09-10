#include "Player.hpp"
#include <iostream>

Player::Player() :
    weapon(nullptr),
    armor(nullptr)
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
