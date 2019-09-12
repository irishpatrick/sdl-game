#pragma once

#include <engine.hpp>
#include "GridSprite.hpp"
#include "Textbox.hpp"

using namespace engine;

class Npc : public GridSprite
{
public:
    Npc();
    ~Npc();

private:
    Textbox text;
};
