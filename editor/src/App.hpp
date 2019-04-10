#pragma once

#include <engine.hpp>
#include "Button.hpp"
#include "Slider.hpp"

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
    static void dragCallback(void*);

private:
    static int running;
    Button test;
    Slider slider;
    engine::Context ctx;
};