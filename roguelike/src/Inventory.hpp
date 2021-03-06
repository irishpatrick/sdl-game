#pragma once

#include <engine.hpp>
#include "Menu.hpp"

using namespace engine;

class Player;
class Item;

class Inventory : public State
{
public:
    Inventory();
    ~Inventory();

    void init();
    void fill(Player*);
    void update();
    void render(float);
    Item* getSelection();

private:
    int gridW;
    int gridH;
    int tileSize;
    int tilePad;
    int numItems;
    std::vector<Item**> grid;
    Player* player;
    Canvas cursor;
    Point selection;
    Menu actions;
    Sprite bg;
};
