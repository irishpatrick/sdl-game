#pragma once

#include <engine.hpp>

class App : public engine::StateBasedGame
{
public:
	App();
	~App();

	void init();
	void update();
	void render();
	void mainLoop();

private:
	engine::Context ctx;
};