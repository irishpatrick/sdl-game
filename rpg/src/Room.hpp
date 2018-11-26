#pragma once

#include <string>
#include <engine.hpp>
#include "Door.hpp"

class Room : public engine::Group
{
public:
    Room() : Group() {}
    ~Room() {}

    void load(const std::string&);
    void update(float);
    void draw(engine::Context&);
	engine::Point getEntry();

private:
	engine::Point entry;
        std::string doorEntryId;
};
