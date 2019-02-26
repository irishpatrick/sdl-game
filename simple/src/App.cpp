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
    engine::MovingAverage<long> avg;
    avg.allocate(10);

    long now, then, delta;
    then = engine::Timer::getNanoTime();

    bool running = true;
    while (running)
    {
        now = engine::Timer::getNanoTime();
        delta = now - then;
        then = now;

        avg.shiftIn(delta);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }
        
        player.update((float)avg.getAverage() / float(1e9));

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
