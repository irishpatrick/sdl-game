#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <engine.h>

#include "stats.hpp"

using namespace std;

class Npc: public engine::Sprite
{
public:
    Npc();
    ~Npc();

    void Json(const string&);

private:
    vector<string> dialogue_;
    //engine::Text* text_;
    Stats stats;
};
