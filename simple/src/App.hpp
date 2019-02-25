#pragma once

#include <engine.hpp>
#include "Ship.hpp"

class App : public engine::SimpleGame
{
public:
    App();
    ~App();

    void init();
    void draw();
    void mainLoop();

private:
    engine::Context ctx;
    Ship player;
    Ship enemies[10];
};