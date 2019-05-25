#include "App.hpp"
#include <cstdint>
#include <ctime>

App::App()
{

}

App::~App()
{

}

void App::init()
{
    srand(time(nullptr));

    ctx.init(512, 480, "Game", false);
    engine::Assets::loadTexture(ctx, "./assets/player.png");
    engine::Assets::loadTexture(ctx, "./assets/enemy.png");
    engine::Assets::loadTexture(ctx, "./assets/missile.png");
    engine::Assets::loadTexture(ctx, "./assets/background.png");

    player.init(ctx);
    player.x = (512/2) - (32/2);
    player.y = 400;
    player.setTexture(engine::Assets::getTexture("player.png"));

    background.init(ctx);
    background.x = 0;
    background.y = 0;
    background.w = 512;
    background.h = 480;
    background.setTexture(engine::Assets::getTexture("background.png"));

    for (int i=0; i<10; i++)
    {
        enemies[i].init(ctx);
    }
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

        for (int i=0; i<10; i++)
        {
            enemies[i].update((float)avg.getAverage() / float(1e9));
            if (enemies[i].y >= 480)
            {
                enemies[i].reset();
            }
            if (engine::Util::simpleCollision(&enemies[i], player.getMissile()))
            {
                enemies[i].reset();
                player.getMissile()->y = 600;
                player.getMissile()->setVisible(false);
            }
        }

        engine::Util::contain(&player, &background);

        player.update((float)avg.getAverage() / float(1e9));

        ctx.clear();
        background.draw(ctx);
        player.draw(ctx);
        for (int i=0; i<10; i++)
        {
            enemies[i].draw(ctx);
        }

        ctx.render();
    }
}

void App::mainLoop()
{
    init();
    draw();
}
