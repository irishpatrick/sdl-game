#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"
#include "Item.hpp"
#include <vector>

using namespace engine;

class Player : public GridSprite
{
public:
    Player();
    ~Player();

private:
    std::vector<Item> inventory;
};
