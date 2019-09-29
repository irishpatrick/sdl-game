#pragma once

#include "Grid.hpp"
#include <engine.hpp>
#include "../../tools/libmaze/include/maze.h"
#include <vector>

using namespace engine;

class Maze : public Grid
{
public:
    Maze();
    ~Maze();

private:
    LM_Maze* maze;
    LM_Grid* grid;
};