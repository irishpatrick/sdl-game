#pragma once

#include <vector>
#include <engine.hpp>

using namespace engine;

class Player;

class Hud : public Sprite
{
public:
    Hud();
    ~Hud();

    void init();
    void setPlayer(Player*);
    void draw();

private:
    Player* player;
    Sprite heart;
};
