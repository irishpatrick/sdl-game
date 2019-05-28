#pragma once

#include <engine.hpp>

class App : public engine::SimpleGame
{
public:
	App() : SimpleGame() {}
	~App() {};

    void update();
	void draw();
	void mainLoop();
};
