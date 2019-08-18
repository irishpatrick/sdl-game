#pragma once

#include "GridSprite.hpp"
#include "Item.hpp"
#include <vector>

class Player : public GridSprite
{
public:
    Player();
    ~Player();

private:
    std::vector<Item> inventory;
};
