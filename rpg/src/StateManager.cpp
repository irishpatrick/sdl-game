#include "StateManager.hpp"

std::map<std::string, engine::State*> StateManager::states = std::map<std::string, engine::State*>();
std::string StateManager::currentState = std::string();

void StateManager::addState(const std::string& key, engine::State* state)
{
    states.insert(std::pair<std::string, engine::State*>(key, state));
}

void StateManager::setCurrentState(const std::string& key)
{
    currentState = key;
}

engine::State* StateManager::getCurrentState()
{
    return states.at(currentState);
}