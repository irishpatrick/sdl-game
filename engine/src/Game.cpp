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

	void Game::draw()
	{

	}

	void Game::mainLoop()
	{
        /*double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;*/
    }

    void Game::run()
    {
        //previous = SDL_GetTicks();
        //lag = 0.0;
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
