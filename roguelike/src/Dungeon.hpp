#pragma once

#include <engine.hpp>
#include "Tilemap.hpp"
#include "Layout.hpp"

using namespace engine;

class Dungeon : public State
{
public:
    Dungeon();
    ~Dungeon();

    void init(Context&);
    void update();
    void render(Context&, float);

private:
    Sprite player;
    Group enemies;
    Tilemap tm;
    Layout lay;
};
