#include "player.h"

Player::Player(): Sprite()
{

}

Player::~Player()
{

}

LocationStack* Player::getDoorStack()
{
    return &doorstack;
}
