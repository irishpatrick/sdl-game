#pragma once

#include <engine.hpp>
#include <string>
#include <map>

class StateManager
{
public:
    static void addState(const std::string&, engine::State*);
    static void setCurrentState(const std::string&);
    static engine::State* getCurrentState();
private:
    static std::map<std::string, engine::State*> states;
    static std::string currentState;
};