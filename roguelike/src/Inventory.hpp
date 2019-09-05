#pragma once

#include <engine.hpp>

using namespace engine;

class Player;

class Inventory : public State
{
public:
    Inventory();
    ~Inventory();

    void init();
    void fill(Player*);
    void update();
    void render(float);

private:
    Player* player;
};