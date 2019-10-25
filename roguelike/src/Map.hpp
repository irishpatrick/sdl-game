#pragma once

#include <string>
#include <engine.hpp>
#include "../../tools/libblk/include/blk.h"
#include "Grid.hpp"

using namespace engine;

class Map : public Grid
{
public:
    Map();
    ~Map();

    int open(const std::string&);
    void draw();

private:
    BLK* store;
};