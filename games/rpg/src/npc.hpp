#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <engine.h>

#include "stats.hpp"
#include "player.hpp"
#include "dialogue.hpp"

class Npc: public engine::Sprite
{
public:
    Npc();
    ~Npc();

    inline void pushLine(const std::string& line) {
        lines.push_back(line);
    }
    void loadJson(const std::string&);
    void interact(engine::Sprite* s, Dialogue*);

private:
    std::vector<std::string> lines;
    Stats stats;
};
