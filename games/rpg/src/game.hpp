#pragma once

#include "config.hpp"
#include "groupmanager.hpp"
#include "player.hpp"
#include "door.hpp"
#include "stats.hpp"
#include "dialogue.hpp"
#include "npc.hpp"

#include <engine.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <future>

using namespace std;

class Game: public engine::State {
public:
    Game(engine::Context*);
    ~Game();

    void init() override;
    void tests();
    void update(float, const uint8_t*) override;
    void render() override;
    void destroy() override;

private:
    Player hero;
    Npc monster;
    engine::Sprite background;
    engine::Sprite animtest;
    engine::Group stage;
    engine::Camera camera;
    GroupManager groups_;
    Door doortest;
    engine::OneShot op;
    engine::OneShot ol;
    vector<engine::Sprite*> hero_collisions;
    engine::ImageFont font;
    Dialogue dlg;
    //gui::List list;
};
