#include "GroupManager.hpp"
#include "Door.hpp"
#include "Npc.hpp"

GroupManager::GroupManager()
{
	activeGroup = nullptr;
    activeId = "";
}

GroupManager::~GroupManager()
{
	for (auto& e : groupMap)
	{
		if (e.second->dynamic)
		{
			delete e.second;
		}
	}
}

void GroupManager::addGroup(const std::string& id, engine::Group* g)
{
    groupMap.insert(pair<string, engine::Group*>(id, g));
}

void GroupManager::loadGroup(const std::string& id, const std::string& fn)
{
    std::ifstream in(fn);
    if (in.fail())
	{
        std::cout << "GroupManager: failed to open json file" << std::endl;
        return;
    }
    nlohmann::json o;
    in >> o;

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
			bool solid = e["solid"];

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
			temp->setSolid(solid);
            temp->setTexture(engine::Assets::getTexture(texture));
            g->add(temp);
            //delete temp;
    	}
    }

    addGroup(id, g);
}

void GroupManager::setEntry(const std::string& tag)
{
    // find entry
    for (auto& e : activeGroup->getSprites())
    {
        if (Door* d = dynamic_cast<Door*>(e))
        {
            // found door
            if (d->getTag() == tag)
            {
                if (focus != nullptr)
                {
                    focus->x = d->GetExit()->x;
                    focus->y = d->GetExit()->y;
                }
            }
        }
    }
}

void GroupManager::setActive(const std::string& id) {
    activeId = id;
    std::map<std::string, engine::Group*>::const_iterator it = groupMap.find(id);
    if (it != groupMap.end()) {
    	if (activeGroup != nullptr) {
    		activeGroup->remove(focus);
    	}
    	activeGroup = groupMap[id];

        // add camera
        /*if (camera != nullptr) {
    		activeGroup->setCamera(camera);
    	}*/

        // add focus
    	if (focus != nullptr) {
    		activeGroup->add(focus);
    	}
    }
}

engine::Group* GroupManager::getActive() {
    return activeGroup;
}

void GroupManager::setFocus(engine::Sprite* s) {
    focus = s;
}
