#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"
#include "Player.hpp"

using namespace engine;

class Enemy : public Player
{
public:
    Enemy();
    ~Enemy();

    void init(Context&);

    void interact(GridSprite*);
};
