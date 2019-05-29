#pragma once

#include <engine.hpp>

class App : public engine::SimpleGame
{
public:
	App() : SimpleGame()
    {
        init();
    }

	~App() {};

    void init();
    void update();
	void draw();
	void mainLoop();

private:
    engine::Context ctx;
};
