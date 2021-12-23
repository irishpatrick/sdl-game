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

	void State::onEntry()
	{

	}

	void State::init(Context& ctx)
	{

	}

	void State::update()
	{
		update(0.0f);
	}

	void State::update(float delta)
	{

	}

	void State::destroy()
	{

	}

	void State::render(Context& ctx)
	{

	}

	void State::render(Context& ctx, float ex)
	{

	}

	void State::render()
	{

	}

	void State::render(float ex)
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

	void State::setName(const std::string& str)
	{
		name = str;
	}

	std::string State::getName()
	{
		return name;
	}
}
