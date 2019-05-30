#include "App.hpp"
#include <string>

void App::init()
{
    ctx.init(1280, 720, "title", false);
    
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
}

void App::update()
{
    ctx.pollEvents();

    const uint8_t* kbd = SDL_GetKeyboardState(NULL);

    bool esc = kbd[SDL_SCANCODE_ESCAPE];
    if (esc)
    {
        quit();
    }

    if (kbd[SDL_SCANCODE_SPACE])
    {
        player.yvel = -1.0f;
    }

    player.yvel += 0.075f;
    
    engine::PlatformerPhysics::resolveCollision(player, platform, 1.0f);
    
    player.y += player.yvel;

    player.update(1.0f);
    platform.update(1.0f);
}

void App::draw()
{
    ctx.clear();

    player.draw(ctx);
    platform.draw(ctx);

    ctx.render();
}

void App::mainLoop()
{
    update();
    draw();
}
