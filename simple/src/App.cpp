#include "App.hpp"
#include <cstdint>

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
    engine::Assets::loadTexture(ctx, "./assets/missile.png");

    player.init(ctx);
    player.x = (512/2) - (32/2);
    player.y = 400;
    player.setTexture(engine::Assets::getTexture("player.png"));

    background.init(ctx);
    background.x = 0;
    background.y = 0;
    background.w = 512;
    background.h = 480;
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

        const uint8_t* keys = SDL_GetKeyboardState(nullptr);
        bool left = keys[SDL_SCANCODE_LEFT];
        bool right = keys[SDL_SCANCODE_RIGHT];
        bool fire = keys[SDL_SCANCODE_SPACE];

        if (left && right)
        {

        }
        else if (left)
        {
            player.left();
        }
        else if (right)
        {
            player.right();
        }

        if (fire)
        {
            player.fire();
        }

        if (player.getMissile()->y <= 0)
        {
            player.getMissile()->setVisible(false);
        }

        engine::Util::contain(&player, &background);

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
