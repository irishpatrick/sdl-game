#include "StateBasedGame.hpp"

namespace engine
{

	StateBasedGame::StateBasedGame()
	{
		currentState = "";
	}

	StateBasedGame::~StateBasedGame()
	{

	}

	void StateBasedGame::addState(const std::string& key, State* state)
	{
		state->setGame(*this);
		states.insert(std::pair<std::string, State*>(key, state));
	}

	void StateBasedGame::setCurrentState(const std::string& key)
	{
		currentState = key;
		states.at(key)->onEntry();
	}

	State* StateBasedGame::getCurrentState()
	{
		return states.at(currentState);
	}

	void StateBasedGame::update()
	{
		getCurrentState()->update();
	}

	void StateBasedGame::draw(float ex)
	{
		getCurrentState()->render(ctx, ex);
	}
}

