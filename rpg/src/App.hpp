#pragma once

#include <engine.hpp>
#include "MyGame.hpp"
#include "Title.hpp"

class App : public engine::StateBasedGame
{
public:
	App();
	~App();

	void init();
	void render();

private:
	MyGame game;
	Title title;
	engine::Context ctx;
	bool quit;
	SDL_Event e;
};