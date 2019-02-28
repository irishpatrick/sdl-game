#include "Game.hpp"

namespace engine
{
	Game::Game()
	{
		ctx = nullptr;
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
}
