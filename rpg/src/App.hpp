#pragma once

#include <engine.hpp>
#include "MyGame.hpp"
#include "Title.hpp"
#include "MapTest.hpp"

class App : public engine::StateBasedGame
{
public:
	App();
	~App();

	void init();
	void draw();
	void mainLoop();

private:
	MyGame game;
	Title title;
	MapTest mapTest;
	engine::Context ctx;
	SDL_Event e;
};
