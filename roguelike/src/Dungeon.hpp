#pragma once

#include <engine.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Chest.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Textbox.hpp"
#include <vector>

using namespace engine;

class Dungeon : public State
{
public:
    Dungeon();
    ~Dungeon();

    void init();
    void update();
    void render(float);

private:
    OneShot prompt;
    OneShot w_once;
    OneShot s_once;
    Player player;
    Enemy enemy;
    Chest chest;
    Grid grid;
    Menu pauseMenu;
    Textbox text;
    std::vector<Menu*> menuStack;
};
