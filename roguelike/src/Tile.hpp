#pragma once

#include <engine.hpp>

using namespace engine;

class Tile : public Sprite
{
public:
    Tile();
    ~Tile();

    bool solid;
};
