#include "groupmanager.h"

GroupManager::GroupManager()
{
	active_ = nullptr;
}

GroupManager::~GroupManager()
{

}

void GroupManager::setassets(Assets* a)
{
	assets_ = a;
}

void GroupManager::addgroup(const std::string& id, Group* g)
{
	groupmap_.insert(std::pair<std::string, Group*>(id, g));
}

void GroupManager::loadgroup(const std::string& id, const std::string& fn)
{
	std::ifstream t(fn);
	std::string data((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	rapidjson::Document json;
	json.Parse(data.c_str());

	Group* g = new Group();

	if (json.HasMember("entry"))
    {
        
    }

	if (json.HasMember("sprites"))
	{
		for (const auto& e : json["sprites"].GetArray())
		{
            // assume sprite object has all required fields
			float x = (float)e["x"].GetInt();
            float y = (float)e["y"].GetInt();
            std::string name = e["name"].GetString();
            std::string texture = e["texture"].GetString();

            // test initialize
            Sprite* temp = new Sprite();
            temp->dynamic = true;
            temp->x = x;
            temp->y = y;
            temp->setTexture(assets_->getTexture(texture));
            g->add(temp);
            //delete temp;
		}
	}
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
