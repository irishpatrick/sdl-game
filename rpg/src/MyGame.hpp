#pragma once

#include "Config.hpp"
#include "GroupManager.hpp"
#include "Player.hpp"
#include "Door.hpp"
#include "Stats.hpp"
#include "Npc.hpp"
#include "Room.hpp"
#include "Enemy.hpp"
#include "DialogueBox.hpp"
#include <engine.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <future>

class MyGame: public engine::State {
public:
    MyGame();
    ~MyGame();

    void init(engine::Context&) override;
    //void input(uint8_t*);
    void onEntry() override;
    void tests();
    void update(float) override;
    void render(engine::Context&) override;
    void destroy() override;

private:
    bool playerInput;
	bool playerMovement;
    Player hero;
    Npc monster;
    engine::Sprite background;
    engine::Group stage;
    engine::Camera camera;
    engine::OneShot op;
    engine::OneShot ol;
    std::vector<engine::Sprite*> hero_collisions;
    DialogueBox box;
    //ui::Dialogue dlg;
	//ui::Decision dec;
    engine::Transition transition;
    Enemy enemytest;
    Door* todo;
    float todo_x;
    float todo_y;
    engine::ScrollingText scTest;

	Room room1;
	Room town1;
	Room room2;
};
