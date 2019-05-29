#include "App.hpp"

void App::init()
{
    std::cout << "init\n";
    ctx.init(1280, 720, "title", false);
}

void App::update()
{
    std::cout << "poll\n";
    ctx.pollEvents();
}

void App::draw()
{
    std::cout << "clear\n";
    ctx.clear();
    std::cout << "render\n";
    ctx.render();
}

void App::mainLoop()
{
    update();
    draw();
}
