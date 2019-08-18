#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"

using namespace engine;

class Enemy : public GridSprite
{
public:
    Enemy();
    ~Enemy();

    void init(Context&);
};
