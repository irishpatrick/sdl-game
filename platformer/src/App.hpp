#pragma once

#include <engine.hpp>

class App : public engine::Game
{
public:
	App() : Game() {}
	~App() {};

	void draw();
	void mainLoop();
};