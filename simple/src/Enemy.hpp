#pragma once

#include <engine.hpp>
#include "Ship.hpp"

class Enemy : public Ship
{
public:
    Enemy();
    ~Enemy();
    
    void init(engine::Context&);
    void reset();
};
