#pragma once

#include <map>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <engine.hpp>
#include "Stats.hpp"

using json = nlohmann::json;

class Player: public engine::KeyFrameSprite
{
public:
    Player();
    ~Player();

	void init(engine::Context&);

    json toJson();
    engine::LocationStack* getDoorStack();

private:
    engine::LocationStack doorstack;
    std::vector<std::string> inventory;
    Stats stats;
};
