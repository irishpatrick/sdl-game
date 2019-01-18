#include "State.hpp"

namespace engine 
{

	State::State() 
	{
		kbd = nullptr;
	}

	State::~State() 
	{

	}

	void State::init(Context& ctx) 
	{

	}

	void State::update(float delta)
	{

	}

	void State::render(Context& ctx) 
	{

	}

	void State::destroy() 
	{

	}

	void State::onEntry()
	{

	}

	void State::updateKeys()
	{
		kbd = (uint8_t*)SDL_GetKeyboardState(nullptr);
	}

	void State::setGame(Game& g)
	{
		game = &g;
	}
}
