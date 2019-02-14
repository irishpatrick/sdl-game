#pragma once

#include <engine.hpp>

class App : public engine::SimpleGame
{
public:
    App();
    ~App();

    void init();
    void draw();
    void mainLoop();
};
