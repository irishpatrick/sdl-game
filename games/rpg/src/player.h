#pragma once

#include <map>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <engine.h>
#include "stats.h"

using namespace std;
using json = nlohmann::json;

class Player: public engine::Sprite
{
public:
    Player();
    ~Player();

    json toJson();
    engine::LocationStack* getDoorStack();

private:
    engine::LocationStack doorstack;
    vector<string> inventory;
    Stats stats;
};
