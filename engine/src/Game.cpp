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

		while (clock.hasLag())
		{
			update();
			clock.lagTick();
		}

		draw(clock.extrapolate());
    }

    void Game::start()
    {
		init();
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
