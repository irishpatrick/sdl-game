#pragma once

#include <engine.hpp>
#include "Dungeon.hpp"

using namespace engine;

class App : public Game
{
public:
    App();
    ~App();

    void init();
    void update();
    void draw(float);

private:
    Context* ctx;
    Dungeon dungeon;
};
