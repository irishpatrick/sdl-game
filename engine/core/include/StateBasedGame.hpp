#pragma once

#include "core_api.hpp"
#include "State.hpp"
#include <string>
#include <map>

class StateBasedGame
{
public:
	StateBasedGame();
	~StateBasedGame();

	CORE_API static void addState(const std::string&, engine::State*);
	CORE_API static void setCurrentState(const std::string&);
	CORE_API static engine::State* getCurrentState();

private:
	static std::map<std::string, engine::State*> states;

};