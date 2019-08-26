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
    std::cout << "received " << item.getName() << std::endl;
    inventory.push_back(item);
}
