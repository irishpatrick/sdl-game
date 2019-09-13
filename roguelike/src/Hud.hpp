#pragma once

#include <engine.hpp>

using namespace engine;

class Player;

class Hud : public Sprite
{
public:
    Hud();
    ~Hud();

    void setPlayer(Player*);

private:
    Player* player;
};