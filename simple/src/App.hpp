#pragma once

#include <engine.hpp>
#include "Ship.hpp"
#include "Enemy.hpp"

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
    SDL_Event e;
    Ship player;
    engine::Sprite background;
    Enemy enemies[10];
};
