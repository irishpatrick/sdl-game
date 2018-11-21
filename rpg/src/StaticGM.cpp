#include "StaticGM.hpp"

std::map<std::string, engine::Group*> StaticGM::groupMap =
    std::map<std::string, engine::Group*>();
engine::Group* StaticGM::activeGroup = nullptr;
engine::Sprite* StaticGM::focus = nullptr;
std::string StaticGM::activeId = std::string();

void StaticGM::addGroup(const std::string& id, engine::Group* group)
{
    groupMap.insert(std::pair<std::string, engine::Group*>(id, group));
}

void StaticGM::setActive(const std::string& id)
{
    activeId = id;
}
