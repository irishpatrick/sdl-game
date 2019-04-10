#pragma once

#include <engine.hpp>
#include "Button.hpp"

class App : public engine::SimpleGame
{
public:
    App();
    ~App();

    void init();
    void update();
    void draw();
    void mainLoop();

    static void quitCallback();
    static void testCallback();

private:
    static int running;
    Button test;
    engine::Context ctx;
};