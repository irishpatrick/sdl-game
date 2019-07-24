#pragma once

#include <engine.hpp>
#include "Tilemap.hpp"

using namespace engine;

class Dungeon : public State
{
public:
    Dungeon();
    ~Dungeon();

    void init(Context&);
    void update(float);
    void render(Context&);

private:
    Sprite player;
    Group enemies;
    Tilemap tm;
};