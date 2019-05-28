#include "Game.hpp"

namespace engine
{
	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	void Game::draw()
	{

	}

	void Game::mainLoop()
	{

    }

    void Game::run()
    {
        while (running)
        {
            mainLoop();
        }
    }

    void Game::quit()
    {
        running = false;
    }
}
