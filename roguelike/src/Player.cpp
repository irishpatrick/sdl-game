#include "Player.hpp"
#include <iostream>

Player::Player()
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
