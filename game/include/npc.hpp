#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <engine.hpp>

#include "stats.hpp"
#include "player.hpp"
#include <ui.hpp>

class Npc: public engine::Sprite
{
public:
    Npc();
    ~Npc();

    inline void pushLine(const std::string& line) {
        lines.push_back(line);
    }
    void loadJson(const std::string&);
    void interact(engine::Sprite* s, ui::Dialogue*);

private:
    std::vector<std::string> lines;
    Stats stats;
};
