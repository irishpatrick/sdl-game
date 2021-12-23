#pragma once

#include "core_api.hpp"
#include "Game.hpp"
#include "State.hpp"
#include <string>
#include <map>

namespace engine
{
	class StateBasedGame : public Game
	{
	public:
		CORE_API StateBasedGame();
		CORE_API virtual ~StateBasedGame();

		CORE_API void addState(const std::string&, State*);
		CORE_API void setCurrentState(const std::string&);
		CORE_API State* getCurrentState();
		
		void update();
		void draw(float);

	private:
		std::map<std::string, State*> states;
		std::string currentState;
	};
}
