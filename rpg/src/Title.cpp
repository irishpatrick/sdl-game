#include "Title.hpp"
#include "StateManager.hpp"
#include <iostream>

void Title::init(engine::Context& ctx)
{
    background.setTexture(engine::Assets::getTexture("title.png"));
    background.x = 0;
    background.y = 0;
}

void Title::update(float delta, const unsigned char* keys)
{
    if (keys[SDL_SCANCODE_RETURN])
    {
        StateManager::setCurrentState("game");
        std::cout << "current state change to game" << std::endl;
    }
}

void Title::render(engine::Context& ctx)
{
    background.draw(ctx);
}