#include "Game.hpp"

namespace engine
{
	bool Game::running = true;

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
