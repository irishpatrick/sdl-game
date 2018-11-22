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
    if (groupMap.find(id) == groupMap.end())
    {
        // todo handle error
        return;
    }

    activeGroup = groupMap[id];
}

engine::Group* StaticGM::getGroup(const std::string& id)
{
    if (groupMap.find(id) == groupMap.end())
    {
        // todo handle error
        return nullptr;
    }

    return groupMap[id];
}

const std::string& StaticGM::getActiveId()
{
    return activeId;
}

engine::Group* StaticGM::getActive()
{
    return activeGroup;
}

void StaticGM::setFocus(engine::Sprite* s)
{
    focus = s;
}
