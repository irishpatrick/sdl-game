#include "App.hpp"

App::App()
{

}

App::~App()
{

}

void App::init()
{
    ctx.init(512, 480, "Game", false);
    engine::Assets::loadTexture(ctx, "./assets/player.png");    

}

void App::draw()
{

}

void App::mainLoop()
{

}