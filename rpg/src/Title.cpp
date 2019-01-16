#include "Title.hpp"
#include "StateManager.hpp"
#include <iostream>

void Title::init(engine::Context& ctx)
{
    background.setTexture(engine::Assets::getTexture("title.png"));
    background.x = ctx.getWidth() / 2 - background.w / 2;
    background.y = ctx.getHeight() / 2 - background.h / 2;

}

void Title::update(float delta)
{
    updateKeys();

    if (kbd[SDL_SCANCODE_RETURN])
    {
		transition.fadeOut(200);
    }

    transition.update();

	if (transition.getStatus() == 1 && !transition.isRunning())
	{
		StateManager::setCurrentState("game");
	}
}

void Title::render(engine::Context& ctx)
{
    background.draw(ctx);
	transition.draw(&ctx);
}
