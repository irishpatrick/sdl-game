#pragma once

#include <engine.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Chest.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include <vector>

using namespace engine;

class Dungeon : public State
{
public:
    Dungeon();
    ~Dungeon();

    void init(Context&);
    void update();
    void render(Context&, float);

private:
    OneShot prompt;
    OneShot w_once;
    OneShot s_once;
    Player player;
    Enemy enemy;
    Chest chest;
    Grid grid;
    Menu menu;
    std::vector<Menu*> menuStack;
};
