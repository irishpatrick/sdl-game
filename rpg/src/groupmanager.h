#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
//#include <rapidjson/document.h>
class Group;
class Sprite;
class Camera;


class GroupManager
{
public:
	GroupManager();
	~GroupManager();

	void addgroup(const std::string&, Group*);
	void loadgroup(const std::string&, const std::string&);
	void setactive(const std::string &);
	void setcamera(Camera*);
	void setfocus(Sprite*);

	Group* getactive();

private:
	std::map<std::string, Group*> groupmap_;
	Group* active_;
	Camera* camera_;
	Sprite* focus_;
};

#endif /* GROUPMANAGER_H */
