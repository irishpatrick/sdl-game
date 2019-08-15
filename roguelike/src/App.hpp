#pragma once

#include <engine.hpp>
#include "Dungeon.hpp"
#include "Tilemap.hpp"

using namespace engine;

class App : public StateBasedGame
{
public:
    App();
    ~App();

    void init();
    void update();
    void draw(float);

private:
    Context ctx;
    Dungeon dungeon;
};
