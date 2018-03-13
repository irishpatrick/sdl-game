#include "groupmanager.h"
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

void GroupManager::addgroup(const string& id, engine::Group* g)
{
    groupmap_.insert(pair<string, engine::Group*>(id, g));
}

void GroupManager::loadgroup(const std::string& id, const std::string& fn)
{
    ifstream i(fn);
    nlohmann::json o;
    i >> o;

    engine::Group* g = new engine::Group();
    g->dynamic = true;

    if (o.find("entry") != o.end())
    {
    	g->sx = o["entry"]["x"];
    	g->sy = o["entry"]["y"];
    }
    if (engine::Util::JsonExists(o, "sprites"))
    {
        for (const auto& e : o["sprites"])
        {
            // assume sprite object has all required fields
            float x = (float)e["x"];
            float y = (float)e["y"];
            string name = e["name"];
            string texture = e["texture"];

            // test initialize
            engine::Sprite* temp = nullptr;
            if (e.find("type") != e.end())
            {
                string type = e["type"];
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
                        printf("setting door exits\n");
                        ref->SetExit(e["exit"]["x"], e["exit"]["y"]);
                    }
                    if (e.find("tag") != e.end())
                    {
                        ref->setTag(e["tag"]);
                    }

                }
                else
                {
                    temp = new engine::Sprite();
                }
            }
            else
            {
                temp = new engine::Sprite();
            }
            temp->dynamic = true;
    		temp->name = name;
            temp->x = x;
            temp->y = y;
            temp->setTexture(engine::Assets::getTexture(texture));
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

void GroupManager::setEntry(const std::string& tag)
{
    // find entry
    for (auto& e : active_->getSprites())
    {
        if (Door* d = dynamic_cast<Door*>(e))
        {
            // found door
            if (d->getTag() == tag)
            {
                if (focus_ != nullptr)
                {
                    focus_->x = d->GetExit()->x;
                    focus_->y = d->GetExit()->y;
                }
            }
        }
    }
}

void GroupManager::setactive(const std::string& id)
{
    map<string, engine::Group*>::const_iterator it = groupmap_.find(id);
    if (it != groupmap_.end())
    {
    	if (active_ != nullptr)
    	{
    		active_->remove(focus_);
    	}
    	active_ = groupmap_[id];

        // add camera
        if (camera_ != nullptr)
    	{
    		active_->setCamera(camera_);
    	}

        // add focus
    	if (focus_ != nullptr)
    	{
    		active_->add(focus_);
    	}
    }
}

engine::Group* GroupManager::getactive()
{
    return active_;
}

void GroupManager::setcamera(engine::Camera* c)
{
    camera_ = c;
}

void GroupManager::setfocus(engine::Sprite* s)
{
    focus_ = s;
}
