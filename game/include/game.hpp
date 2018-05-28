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
    void input(uint8_t*);
    void tests();
    void update(float, const uint8_t*) override;
    void render() override;
    void destroy() override;

private:
    bool playerInput;
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
    engine::Transition transition;
    Door* todo;
    float todo_x;
    float todo_y;
    //gui::List list;
};
