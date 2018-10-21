#include "Title.hpp"
#include "StateManager.hpp"
#include <iostream>

void Title::init(engine::Context& ctx)
{
    background.setTexture(engine::Assets::getTexture("title.png"));
    background.x = ctx.getWidth() / 2 - background.w / 2;
    background.y = ctx.getHeight() / 2 - background.h / 2;
	
}

void Title::update(float delta, const unsigned char* keys)
{
    if (keys[SDL_SCANCODE_RETURN])
    {
		transition.fadeOut(200);
        std::cout << "current state change to game" << std::endl;
    }

	if (transition.getStatus() && !transition.isRunning())
	{
		StateManager::setCurrentState("game");
	}
}

void Title::render(engine::Context& ctx)
{
	transition.draw(&ctx);
    background.draw(ctx);
}