#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <map>
#include "group.h"
#include "sprite.h"
#include "camera.h"

class GroupManager
{
public:
	GroupManager();
	~GroupManager();

	void addgroup(const std::string&, Group*);
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