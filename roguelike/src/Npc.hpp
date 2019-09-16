#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"

using namespace engine;

class Npc : public GridSprite
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
