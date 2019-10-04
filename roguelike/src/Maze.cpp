#include "Maze.hpp"
#include <iostream>
#include <stack>

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
    int i;
    int j;

    // generate the maze and assemble the grid of tiles
    if (atlas == nullptr || tiles.size() < 1)
    {
        return;
    }
    lm_maze = maze_generate_with_rooms(mw, mh);

    // pick a random point
    /*PointT<int> corner;
    corner.x = 2;
    corner.y = 2;
    int len = 4;
    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < len; ++j)
        {
            LM_Cell* c = maze_get(lm_maze, corner.x + j, corner.y + i);
            c->e = 0;
            c->n = 0;
            c->w = 0;
            c->s = 0;
        }
    }*/

    lm_grid = maze_format(lm_maze, 1);

    w = lm_grid->dimension.x;
    h = lm_grid->dimension.y;

    grid.clear();

    for (i = 0; i < lm_grid->dimension.y; ++i)
    {
        for (j = 0; j < lm_grid->dimension.x; ++j)
        {
            int t = (int)grid_get(lm_grid, j, i);
            grid.push_back(tiles[t * 3]);
        }
    }
}