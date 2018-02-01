#include "groupmanager.h"
#include "assets.h"
#include "group.h"
#include "sprite.h"
#include "camera.h"
#include "util.h"
#include "door.h"

GroupManager::GroupManager()
{
	active_ = nullptr;
}

GroupManager::~GroupManager()
{
	for (auto& e : groupmap_)
	{
		if (e.second->dynamic)
		{
			delete e.second;
		}
	}
}

void GroupManager::addgroup(const std::string& id, Group* g)
{
	groupmap_.insert(std::pair<std::string, Group*>(id, g));
}

void GroupManager::loadgroup(const std::string& id, const std::string& fn)
{
    std::ifstream i(fn);
    nlohmann::json o;
    i >> o;

    Group* g = new Group();
    g->dynamic = true;

    if (o.find("entry") != o.end())
    {
    	g->sx = o["entry"]["x"];
    	g->sy = o["entry"]["y"];
    }
    if (Util::JsonExists(o, "sprites"))
    {
        for (const auto& e : o["sprites"])
        {
            // assume sprite object has all required fields
            float x = (float)e["x"];
            float y = (float)e["y"];
            std::string name = e["name"];
            std::string texture = e["texture"];

            // test initialize
            Sprite* temp = nullptr;
            if (e.find("type") != e.end())
            {
                std::string type = e["type"];
                if (type == "door")
                {
                    temp = new Door();
                    Door* ref = (Door*)temp;
                    if (e.find("dest") != e.end())
                    {
                        ref->SetDest(e["dest"]);
                        ref->SetManager(this);
                    }
                    if (e.find("exit") != e.end())
                    {
                        ref->SetExit(e["exit"]["x"], e["exit"]["y"]);
                    }

                }
                else
                {
                    temp = new Sprite();
                }
            }
            else
            {
                temp = new Sprite();
            }
            temp->dynamic = true;
    		temp->name = name;
            temp->x = x;
            temp->y = y;
            temp->setTexture(Assets::getTexture(texture));
            g->add(temp);
            //delete temp;
    	}
    }

    addgroup(id, g);

    /*rapidjson::Document json;
    json.Parse(data.c_str());

    Group* g = new Group();
    g->dynamic = true;

    if (json.HasMember("entry"))
    {
        focus_->x = json["entry"]["x"].GetInt();
    	focus_->y = json["entry"]["y"].GetInt();
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

    addgroup(id, g);*/
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
    	focus_->x = active_->sx;
    	focus_->y = active_->sy;
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
