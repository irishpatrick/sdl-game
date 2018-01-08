#include "groupmanager.h"

GroupManager::GroupManager()
{
	active_ = nullptr;
}

GroupManager::~GroupManager()
{

}

void GroupManager::addgroup(const std::string& id, Group* g)
{
	groupmap_.insert(std::pair<std::string, Group*>(id, g));
}

void GroupManager::setactive(const std::string& id)
{
	std::map<std::string, Group*>::const_iterator it = groupmap_.find(id);
	if (it != groupmap_.end())
	{
		if (active_ != nullptr)
		{
			active_->remove(focus_);
		}
		active_ = groupmap_[id];
		if (camera_ != nullptr)
		{
			active_->setCamera(camera_);
		}
		if (focus_ != nullptr)
		{
			active_->add(focus_);
		}
	}
}

Group* GroupManager::getactive()
{
	return active_;
}

void GroupManager::setcamera(Camera* c)
{
	camera_ = c;
}

void GroupManager::setfocus(Sprite* s)
{
	focus_ = s;
}
