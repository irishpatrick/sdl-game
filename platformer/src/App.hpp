#pragma once

#include <engine.hpp>
#include "Player.hpp"
#include "Camera.hpp"

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
    Player player;
    engine::Sprite platform;
    engine::Sprite platform2;

    engine::Group sprites;
    engine::Group platforms;

    Camera camera;
};
