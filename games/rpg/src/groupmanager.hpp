#pragma once

#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <engine.hpp>

using namespace std;

class GroupManager
{
public:
	GroupManager();
	~GroupManager();

	void addgroup(const string&, engine::Group*);
	void loadgroup(const string&, const string&);
	void setactive(const string&);
    void setEntry(const string&);
	void setcamera(engine::Camera*);
	void setfocus(engine::Sprite*);

	engine::Group* getactive();

private:
	map<string, engine::Group*> groupmap_;
	engine::Group* active_;
	engine::Camera* camera_;
	engine::Sprite* focus_;
};
