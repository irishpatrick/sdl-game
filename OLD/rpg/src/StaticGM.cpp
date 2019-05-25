#include "StaticGM.hpp"
#include "Door.hpp"

std::map<std::string, engine::Group*> StaticGM::groupMap =
    std::map<std::string, engine::Group*>();
engine::Group* StaticGM::activeGroup = nullptr;
engine::Sprite* StaticGM::focus = nullptr;
std::string StaticGM::activeId = std::string();

void StaticGM::addGroup(const std::string& id, engine::Group* group)
{
	std::cout << "adding group " << id << std::endl;
    groupMap.insert(std::pair<std::string, engine::Group*>(id, group));
}

void StaticGM::setEntry(const std::string& tag)
{
	if (activeGroup == nullptr)
	{
		std::cout << "no group was set active" << std::endl;
		return;
	}
	for (auto& e : activeGroup->getSprites())
	{
		if (Door* d = dynamic_cast<Door*>(e))
		{
			if (d->getTag() == tag)
			{
				if (focus != nullptr)
				{
					focus->x = d->GetExit()->x;
					focus->y = d->GetExit()->y;
				}
			}
		}
	}
}

void StaticGM::setActive(const std::string& id)
{
    activeId = id;
    if (groupMap.find(id) == groupMap.end())
    {
		std::cout << "setActive() error" << std::endl;
        // todo handle error
        return;
    }

    activeGroup = groupMap[id];

	activeGroup->add(focus);
}

engine::Group* StaticGM::getGroup(const std::string& id)
{
    if (groupMap.find(id) == groupMap.end())
    {
		std::cout << "getGroup() error" << std::endl;
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
