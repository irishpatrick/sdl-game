#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <engine.hpp>
#include <ui.hpp>

class Battle: public engine::State {
public:
    Battle();
    ~Battle();

    void setBackground(const std::string&);
    void addCombatants(std::vector<engine::Sprite*>&, std::vector<engine::Sprite*>&);

    void init(engine::Context&) override;
    void update(float, const uint8_t*) override;
    void render(engine::Context&) override;
    void destroy() override;

private:
    std::vector<engine::Sprite> enemies;
    std::vector<engine::Sprite> allies;
    engine::Sprite bg;
    engine::ImageFont font;
    ui::Dialogue dialogue;
};
