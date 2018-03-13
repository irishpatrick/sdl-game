#include "player.h"

Player::Player(): Sprite()
{

}

Player::~Player()
{

}

engine::LocationStack* Player::getDoorStack()
{
    return &doorstack;
}
