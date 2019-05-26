#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <engine.hpp>

class GroupManager
{
public:
	GroupManager();
	~GroupManager();

	void addGroup(const std::string&, engine::Group*);
	void loadGroup(const std::string&, const std::string&);
	void setActive(const std::string&);
    void setEntry(const std::string&);
	void setFocus(engine::Sprite*);

    inline engine::Group* getGroup(const std::string& id)
	{
        return groupMap[id];
    }

    inline std::string getActiveId()
	{
        return activeId;
    }

	engine::Group* getActive();

private:
	std::map<std::string, engine::Group*> groupMap;
	engine::Group* activeGroup;
	engine::Sprite* focus;
    std::string activeId;
};
