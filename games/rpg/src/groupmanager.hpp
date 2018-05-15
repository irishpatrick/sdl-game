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

	void addgroup(const std::string&, engine::Group*);
	void loadgroup(const std::string&, const string&);
	void setactive(const std::string&);
    void setEntry(const std::string&);
	void setcamera(engine::Camera*);
	void setfocus(engine::Sprite*);

    inline engine::Group* getGroup(const std::string& id) {
        return groupmap_[id];
    }

    inline std::string getActiveId() {
        return active_id;
    }

	engine::Group* getactive();

private:
	std::map<std::string, engine::Group*> groupmap_;
	engine::Group* active_;
	engine::Camera* camera_;
	engine::Sprite* focus_;
    std::string active_id;
};
