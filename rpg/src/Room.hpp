#pragma once

#include <string>
#include <engine.hpp>
#include "Door.hpp"
#include "Npc.hpp"

class Room : public engine::Group
{
public:
    Room() : Group() {}
    ~Room() {}

    void load(const std::string&);
    void update(float);
    void draw(engine::Context&);
	engine::Point getEntry();

	std::vector<Npc*> getNpcs();

private:
	engine::Point entry;
    std::string doorEntryId;
};
