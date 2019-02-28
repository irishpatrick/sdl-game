#include "Game.hpp"

namespace engine
{
	Game::Game()
	{
		ctx = nullptr;
		running = true;
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

	void Game::attachContext(Context& c)
	{
		ctx = &c;
	}

	Context* Game::getContext()
	{
		return ctx;
	}

	void Game::quit()
	{
		running = false;
	}
}
