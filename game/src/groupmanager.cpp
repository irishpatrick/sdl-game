#include "groupmanager.hpp"
#include "door.hpp"
#include "npc.hpp"

GroupManager::GroupManager()
{
	active_ = nullptr;
    active_id = "";
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

void GroupManager::addgroup(const std::string& id, engine::Group* g)
{
    groupmap_.insert(pair<string, engine::Group*>(id, g));
}

void GroupManager::loadgroup(const std::string& id, const std::string& fn)
{
    std::ifstream i(fn);
    nlohmann::json o;
    i >> o;

    engine::Group* g = new engine::Group();
    g->dynamic = true;

    if (o.find("entry") != o.end())
    {
    	g->sx = o["entry"]["x"];
    	g->sy = o["entry"]["y"];
    }
    if (o.find("sprites") != o.end())
    {
        for (const auto& e : o["sprites"])
        {
            // assume sprite object has all required fields
            float x = (float)e["x"];
            float y = (float)e["y"];
            std::string name = e["name"];
            std::string texture = e["texture"];

            // test initialize
            engine::Sprite* temp = nullptr;
            if (e.find("type") != e.end())
            {
                std::string type = e["type"];
                if (type == "door")
                {
                    temp = new Door();
                    Door* ref = (Door*)temp;
                    printf("setting door exits\n");
                    ref->SetExit(e["x"], e["y"].get<int>()+40);
                    if (e.find("dest") != e.end())
                    {
                        ref->SetDest(e["dest"]);
                        ref->SetManager(this);
                    }
                    if (e.find("tag") != e.end())
                    {
                        ref->setTag(e["tag"]);
                    }

                }
                else if (type == "npc") {
                    temp = new Npc();
                    Npc* ref = (Npc*)temp;
                    if (e.find("dialogue") != e.end()) {
                        for (auto& line : e["dialogue"]) {
                            ref->pushLine(line.get<std::string>());
                        }
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

void GroupManager::setactive(const std::string& id) {
    active_id = id;
    std::map<std::string, engine::Group*>::const_iterator it = groupmap_.find(id);
    if (it != groupmap_.end()) {
    	if (active_ != nullptr) {
    		active_->remove(focus_);
    	}
    	active_ = groupmap_[id];

        // add camera
        if (camera_ != nullptr) {
    		active_->setCamera(camera_);
    	}

        // add focus
    	if (focus_ != nullptr) {
    		active_->add(focus_);
    	}
    }
}

engine::Group* GroupManager::getactive() {
    return active_;
}

void GroupManager::setcamera(engine::Camera* c) {
    camera_ = c;
}

void GroupManager::setfocus(engine::Sprite* s) {
    focus_ = s;
}
