#include "player.h"

Player::Player(): Sprite()
{

}

Player::~Player()
{

}

json Player::toJson() {
    json o;

    int i = 0;
    for (auto& e : inventory) {

        o["inventory"][i++] = e;
    }
}

engine::LocationStack* Player::getDoorStack()
{
    return &doorstack;
}
