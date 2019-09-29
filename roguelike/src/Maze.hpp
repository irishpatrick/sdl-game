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

    void generate(int, int);

private:
    LM_Maze* lm_maze;
    LM_Grid* lm_grid;
};