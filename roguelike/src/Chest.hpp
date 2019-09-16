#pragma once

#include "GridSprite.hpp"
#include "Item.hpp"
#include "Textbox.hpp"
#include <engine.hpp>
#include <vector>

using namespace engine;

class Chest : public GridSprite
{
public:
    Chest();
    ~Chest();

    void init(Context&);
    void interact(GridSprite*);

    void fill();

private:
    std::vector<Item> contents;
    bool searched;
    Textbox text;
};
