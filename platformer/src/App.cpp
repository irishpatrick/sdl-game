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
    player.yvel = 0.1f;

    platform.init(ctx);
    platform.setTexture(engine::Assets::getTexture("platform.png"));
    platform.x = 10;
    platform.y = 100;
    platform.setBoundingBox(0, 0, platform.w, platform.h);
}

void App::update()
{
    ctx.pollEvents();

    player.setBoundingBox(player.x, player.y, player.w, player.h);
    
    std::string dir = engine::Util::checkCollision(&player, &platform);
    //std::cout << dir << "\n";
    if (dir == "north")
    {
        std::cout << "ground\n";
    }

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
