#include "Game.hpp"
#include <SDL.h>

namespace engine
{
	bool Game::running = true;

	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	void Game::init()
	{

	}

	void Game::update()
	{

	}

	void Game::draw(float ex)
	{

	}

	void Game::loop()
	{
		clock.tick();
		ctx.pollEvents();

		while (clock.hasLag())
		{
			internalUpdate();
			update();
			clock.lagTick();
		}

		internalDraw();
		
		ctx.clear();
		draw(clock.extrapolate());
		ctx.render();

		clock.back();
    }

    void Game::start()
    {
		init();
		clock.start();
        while (running)
		{
			loop();
		}
    }

    void Game::quit()
    {
        running = false;
    }
}
