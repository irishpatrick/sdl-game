#include "App.hpp"
#include <string>

void App::init()
{
    ctx.init(512, 480, "title", false);
    
    engine::Assets::loadTexture(ctx, "assets/test_char.png");
    engine::Assets::loadTexture(ctx, "assets/platform.png");

    player.init(ctx);
    player.setTexture(engine::Assets::getTexture("test_char.png"));
    player.x = 10;
    player.y = 10;
    player.setBoundingBox(0, 0, player.w, player.h);
    //player.yvel = 0.1f;
    player.solid = true;

    platform.init(ctx);
    platform.setTexture(engine::Assets::getTexture("platform.png"));
    platform.x = 10;
    platform.y = 400;
    platform.setBoundingBox(0, 0, platform.w, platform.h);
    platform.solid = true;

    platform2.init(ctx);
    platform2.setTexture(engine::Assets::getTexture("platform.png"));
    platform2.x = 200;
    platform2.y = 350;
    platform2.setBoundingBox(0, 0, platform2.w, platform2.h);
    platform2.solid = true;
}

void App::update()
{
    engine::PlatformerPhysics::resolveCollision(player, platform, 1.0f);
    engine::PlatformerPhysics::resolveCollision(player, platform2, 1.0f);

    ctx.pollEvents();

    const uint8_t* kbd = SDL_GetKeyboardState(NULL);

    bool esc = kbd[SDL_SCANCODE_ESCAPE];
    bool reset = kbd[SDL_SCANCODE_R];
    bool jump = kbd[SDL_SCANCODE_SPACE];
    bool left = kbd[SDL_SCANCODE_LEFT];
    bool right = kbd[SDL_SCANCODE_RIGHT];

    if (esc)
    {
        quit();
    }

    if (jump)
    {
        player.jump(1.0f);
    }

    if (reset)
    {
        player.x = 10;
        player.y = 10;
        player.yvel = 0;
        player.xvel = 0;
    }

    if (!left && !right)
    {
        player.move(0.0f);
    }

    if (left)
    {
        player.move(-1.0f);
    }

    if (right)
    {
        player.move(1.0f);
    }

    player.yvel += 0.075f;
    
    player.y += player.yvel;

    player.update(1.0f);
    platform.update(1.0f);
    platform2.update(1.0f);
}

void App::draw()
{
    ctx.clear();

    player.draw(ctx);
    platform.draw(ctx);
    platform2.draw(ctx);

    ctx.render();
}

void App::mainLoop()
{
    update();
    draw();
}