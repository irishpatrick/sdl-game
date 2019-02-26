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

    player.x = 10;
    player.y = 10;
    player.setTexture(engine::Assets::getTexture("player.png"));
}

void App::draw()
{
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        ctx.clear();

        player.draw(ctx);

        ctx.render();
    }
}

void App::mainLoop()
{
    init();
    draw();
}
