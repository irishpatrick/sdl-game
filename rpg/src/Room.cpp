#include "Room.hpp"
#include "Npc.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

void Room::load(const std::string& fn)
{
    std::cout << "loading room " << fn << std::endl;
    std::ifstream in(fn);
    if (in.fail())
    {
        std::cout << "failed to open " << fn << std::endl;
        return;
    }

    json o;
    in >> o;

    if (o.find("entry") != o.end())
    {
        sx = o["entry"]["x"].get<float>();
        sy = o["entry"]["y"].get<float>();
		entry.set(sx, sy);
    }
    else
    {
        std::cout << "bad entry format" << std::endl;
	return;
    }

    if (o.find("doorentry") != o.end())
    {
        doorEntryId = o["doorentry"].get<std::string>();
    }

    if (o.find("sprites") != o.end())
    {
        for (const auto& e : o["sprites"])
        {
            // now we're assuming that the format is correct
			// probably not a good idea for debugging
            float x = (float) e["x"];
            float y = (float) e["y"];
            std::string name = e["name"];
            std::string texture = e["texture"];
            bool solid = e["solid"];

            engine::Sprite* sprite = nullptr;
            if (e.find("type") != e.end())
            {
                std::string type = e["type"];
                if (type == "door")
                {
                    sprite = new Door();
                    Door* ref = (Door*) sprite;
                    ref->SetExit(e["x"].get<int>(), e["y"].get<int>()+40);
                    if (e.find("dest") != e.end())
                    {
                        ref->SetDest(e["dest"]);
                    }
                    if (e.find("tag") != e.end())
                    {
                        ref->setTag(e["tag"]);
                    }
                }
				else if (type == "npc")
				{
					sprite = new Npc();
					Npc* ref = (Npc*)sprite;
					if (e.find("dialogue") != e.end())
					{
						for (auto& line : e["dialogue"])
						{
							ref->pushLine(line.get<std::string>());
						}
					}
				}
				else
				{
					// possible leak
					sprite = new engine::Sprite();
				}
            }
			else
			{
				sprite = new engine::Sprite();
			}
			if (sprite != nullptr)
			{
				sprite->dynamic = true;
				sprite->name = name;
				sprite->x = x;
				sprite->y = y;
				sprite->setSolid(solid);
				sprite->setTexture(engine::Assets::getTexture(texture));
				add(sprite);
			}
			else
			{
				std::cout << "error sprite was null" << std::endl;
			}
        }
    }
	else
	{
		std::cout << "bad sprite format" << std::endl;
		return;
	}

	engine::Sprite* s = get_sprite_by_name(doorEntryId);
	if (s != nullptr)
	{
		std::cout << "set doorentry field" << std::endl;
		entry.set(s->x, s->y);
	}
}

std::vector<Npc*> Room::getNpcs()
{
	std::vector<Npc*> npcList;

	Npc* current;
	for (auto& e : renderList)
	{
		
		if ((current = dynamic_cast<Npc*>(e)))
		{
			npcList.push_back(current);
		}
	}

	return npcList;
}

void Room::update(float delta)
{
    Group::update(delta);
}

void Room::draw(engine::Context& ctx)
{
    Group::draw(ctx);
}

engine::Point Room::getEntry()
{
	return entry;
}
