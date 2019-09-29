#include "Maze.hpp"

Maze::Maze() :
    Grid(),
    lm_maze(nullptr),
    lm_grid(nullptr)
{

}

Maze::~Maze()
{
    if (lm_maze != nullptr)
    {
        maze_free(lm_maze);
    }

    if (lm_grid != nullptr)
    {
        grid_free(lm_grid);
    }
}

void Maze::generate(int w, int h)
{
    if (atlas == nullptr || tiles.size() < 1)
    {
        return;
    }
    lm_maze = maze_generate(w, h);
    lm_grid = maze_format(lm_maze, 1);
}