#include "Maze.hpp"
#include <iostream>

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

void Maze::generate(int mw, int mh)
{
    if (atlas == nullptr || tiles.size() < 1)
    {
        return;
    }
    lm_maze = maze_generate(mw, mh);
    lm_grid = maze_format(lm_maze, 4);

    w = lm_grid->dimension.x;
    h = lm_grid->dimension.y;

    grid.clear();

    int i;
    int j;
    for (i = 0; i < lm_grid->dimension.y; ++i)
    {
        for (j = 0; j < lm_grid->dimension.x; ++j)
        {
            int t = (int)grid_get(lm_grid, j, i);
            //std::cout << t << " ";
            grid.push_back(tiles[t * 3]);
        }
        //std::cout << std::endl;
    }
}