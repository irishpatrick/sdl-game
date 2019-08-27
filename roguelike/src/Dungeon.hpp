#pragma once

#include <engine.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Chest.hpp"
#include "Enemy.hpp"

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
    Player player;
    Enemy test;
    Enemy enemy;
    Chest chest;
    Grid grid;
};
