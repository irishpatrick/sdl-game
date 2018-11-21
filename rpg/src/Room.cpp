#include "Room.hpp"
#include "Door.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Room::load(const std::string& fn)
{
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
        sx = o["entry"]["x"];
        sy = o["entry"]["y"];
    }
    if (o.find("prites") != o.end())
    {
        for (const auto& e : o["sprites"])
        {
            // now we're making assumptions
            float x = (float) e["x"];
            float y = (float) e["y"];
            std::string name = e["name"];
            std::string texture = e["texture"];
            bool solid = e["solid"];

            engine::Sprite* sprite;
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
            }
        }
    }
}

void Room::update(float delta)
{
    Group::update(delta);
}

void Room::draw(engine::Context& ctx)
{
    Group::draw(ctx);
}
