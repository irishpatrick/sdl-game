#pragma once

#include "dialogue.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <engine.h>

class Battle: public engine::State {
public:
    Battle(engine::Context*);
    ~Battle();

    void setBackground(const std::string&);
    void addCombatants(std::vector<engine::Sprite*>&, std::vector<engine::Sprite*>&);

    void init() override;
    void update(float, const uint8_t*) override;
    void render() override;
    void destroy() override;

private:
    std::vector<engine::Sprite> enemies;
    std::vector<engine::Sprite> allies;
    engine::Sprite bg;
    engine::ImageFont font;
    Dialogue dialogue;
};
