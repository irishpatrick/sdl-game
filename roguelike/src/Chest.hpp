#pragma once

#include "GridSprite.hpp"

class Chest : public GridSprite
{
public:
    Chest();
    ~Chest();

    void init(Context&);
};
