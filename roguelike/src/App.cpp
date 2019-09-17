#include "App.hpp"
#include "Config.hpp"
#include "Item.hpp"
#include "Textbox.hpp"

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
    Assets::loadTexture("assets/sprites/sword.png");
    Assets::loadTexture("assets/sprites/heart.png");
    Assets::loadTexture("assets/sprites/inventory.png");

    Item::load("assets/items/apple.json");
    Item::load("assets/items/frying_pan.json");
    Item::load("assets/items/sword.json");

    Textbox::init();

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
