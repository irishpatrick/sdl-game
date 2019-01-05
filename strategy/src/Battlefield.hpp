#pragma once

#include <engine.hpp>
#include "Team.hpp"

class Battlefield : public engine::State
{
public:
    Battlefield();
    ~Battlefield();

    void init(engine::Context&);
    void update(engine::Context&, const uint8_t*);
    void render(engine::Context&);

    void setPlayerTeam(Team&);
    void setEnemyTeam(Team&);
    void setBackground(const std::string&);

private:
    engine::Sprite background;
    engine::Group obstacles;
    engine::Group playerTeam;
    engine::Group enemyTeam;
};
