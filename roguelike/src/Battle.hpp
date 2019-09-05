#pragma once

#include <engine.hpp>

using namespace engine;

class Battle : public State
{
public:
    Battle();
    ~Battle();
    
    void init();
    void update();
    void draw(float);
};