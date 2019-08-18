#include "App.hpp"

App::App()
{

}

App::~App()
{

}

void quit_cb()
{
    exit(0);
}

void App::init()
{
    ctx.init(512, 480, "Roguelike", false);
    ctx.setQuitCallback(quit_cb);

    Assets::loadTexture(ctx, "assets/player.png");
    Assets::loadTexture(ctx, "assets/atlas.png");
    Assets::loadTexture(ctx, "assets/chest.png");
    Assets::loadTexture(ctx, "assets/enemy.png");

    dungeon.init(ctx);

    addState("dungeon", &dungeon);
    setCurrentState("dungeon");
}

void App::update()
{
    ctx.pollEvents();
    getCurrentState()->update();
}

void App::draw(float ex)
{
    ctx.clear();
    getCurrentState()->render(ctx, ex);
    ctx.render();
}
