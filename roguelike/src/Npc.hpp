#pragma once

#include <engine.hpp>
#include "Player.hpp"

using namespace engine;

class Npc : public Player
{
public:
    Npc();
    ~Npc();

    void init();
    void update();
    void draw(float);

    void interact(GridSprite*);

private:
};
