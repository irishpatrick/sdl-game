#pragma once

#include <engine.hpp>

using namespace engine;

class Inventory : public State
{
public:
    Inventory();
    ~Inventory();

    void init();
    void update();
    void draw(float);
};