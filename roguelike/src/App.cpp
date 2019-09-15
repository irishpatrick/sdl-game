#include "App.hpp"
#include "Config.hpp"

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
    Config::load("assets/config.json");

    ctx = &MyEngine::getContext();
    ctx->init(512, 480, "Roguelike", false);
    ctx->setQuitCallback(quit_cb);

    Assets::loadTexture("assets/sprites/player.png");
    Assets::loadTexture("assets/sprites/atlas.png");
    Assets::loadTexture("assets/sprites/chest.png");
    Assets::loadTexture("assets/sprites/enemy.png");
    Assets::loadTexture("assets/sprites/apple.png");
    Assets::loadTexture("assets/sprites/frying_pan.png");

    dungeon.init();
    MyEngine::addState(&dungeon);
    MyEngine::setCurrentState("dungeon");

    inventory.init();
    MyEngine::addState(&inventory);
}

void App::update()
{
    ctx->pollEvents();
    MyEngine::getCurrentState()->update();
}

void App::draw(float ex)
{
    ctx->clear();
    MyEngine::getCurrentState()->render(ex);
    ctx->render();
}
