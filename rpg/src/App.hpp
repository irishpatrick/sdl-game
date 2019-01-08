#pragma once

#include <engine.hpp>
#include "Game.hpp"
#include "Title.hpp"

class App : public engine::StateBasedGame
{
public:
	App();
	~App();

	void init();
	void render();

private:
	Game game;
	Title title;
	engine::Context ctx;
	bool quit;
	SDL_Event e;
};