#pragma once

#include <engine.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Chest.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Npc.hpp"
#include "Hud.hpp"
#include "Maze.hpp"
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
    Camera camera;
    Player player;
    Enemy enemy;
    Chest chest;
    Grid grid;
    Npc npcTest;
    Menu pauseMenu;
    Hud hud;
    std::vector<Menu*> menuStack;
    PointT<float> tpf;
    PointT<int> tpi;
    Maze mazetest;
    Light lighttest;
};
