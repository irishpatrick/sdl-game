#pragma once

#include <engine.hpp>

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
};
