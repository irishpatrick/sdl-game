#pragma once

#include <engine.hpp>
#include <SDL.h>

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
};
