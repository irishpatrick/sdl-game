#pragma once

#include "config.hpp"
#include "groupmanager.hpp"
#include "player.hpp"
#include "door.hpp"
#include "stats.hpp"
#include "npc.hpp"
#include "enemy.hpp"
#include <ui.hpp>
#include <engine.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <future>

class Game: public engine::State {
public:
    Game();
    ~Game();

    void init(engine::Context&) override;
    //void input(uint8_t*);
    void tests();
    void update(float, const uint8_t*) override;
    void render(engine::Context&) override;
    void destroy() override;

private:
    bool playerInput;
    Player hero;
    Npc monster;
    engine::Sprite background;
    engine::Group stage;
    engine::Camera camera;
    GroupManager groups_;
    Door doortest;
    engine::OneShot op;
    engine::OneShot ol;
    std::vector<engine::Sprite*> hero_collisions;
    engine::ImageFont font;
    ui::Dialogue dlg;
	ui::Decision dec;
    engine::Transition transition;
    Enemy enemytest;
    Door* todo;
    engine::DebugInfo debug;
    float todo_x;
    float todo_y;
};
