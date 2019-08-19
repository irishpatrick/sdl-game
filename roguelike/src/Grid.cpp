#include "Grid.hpp"
#include "Tile.hpp"
#include "GridSprite.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool json_has(json& o, const std::string& name)
{
    return o.find(name) != o.end();
}

Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::load(Context& ctx, const std::string& fn)
{
    std::ifstream in(fn);

    if (!in.is_open())
    {
        std::cout << "cannot open " << fn << "\n";
        return;
    }
    json o;
    in >> o;
    in.close();

    if (!json_has(o, "size"))
    {
        return;
    }
    w = o["size"][0].get<int>();
    h = o["size"][1].get<int>();
    size = o["size"][2].get<int>();
    padding = o["size"][3].get<int>();
    border = o["size"][4].get<int>();

    if (!json_has(o, "atlas"))
    {
        return;
    }
    atlas = Assets::getTexture(o["atlas"]);
    if (atlas == nullptr)
    {
        std::cout << "cannot find texture " << o["atlas"] << "\n";
    }

    if (!json_has(o, "tiles"))
    {
        return;
    }
    for (auto& e : o["tiles"])
    {
        Tile* tile = new Tile();
        int x = e[0].get<int>();
        int y = e[1].get<int>();
        Texture* tex = new Texture(atlas->subTexture(
            ctx,
            border + (x * size) + (x * padding),
            border + (y * size) + (y * padding),
            e[2].get<int>(),
            e[3].get<int>()
        ));
        Assets::registerTexture(ctx, tex, ""); // let Assets handle disposal
        tile->setTexture(tex);
        tile->solid = (bool)e[4].get<int>();
        tiles.push_back(tile);
    }

    if (!json_has(o, "data"))
    {
        return;
    }
    for (auto& e : o["data"])
    {
        grid.push_back(tiles[e.get<int>()]);
    }
}

GridSprite* Grid::at(int x, int y)
{
    GridSprite* g = nullptr;
    for (auto& e : children)
    {
        g = dynamic_cast<GridSprite*>(e);
        if (g)
        {
            if (g->getGridPos().equals(Point(x, y)))
            {
                break;
            }
        }
        g = nullptr;
    }

    return g;
}

void Grid::draw(Context& ctx, float ex)
{
    int r = 0;
    int c = 0;
    int i = 0;
    for (auto& e : grid)
    {
        r = i / w;
        c = i % w;

        e->x = c * 32;
        e->y = r * 32;
        e->draw(ctx, ex);

        ++i;
    }
}

int Grid::ctoi(int x, int y)
{
    return y * h + x;
}

Point Grid::itoc(int i)
{
    Point p;
    p.x = i % w;
    p.y = i / w;
    return p;
}

bool Grid::checkMove(int x, int y)
{
    int index = ctoi(x, y);
    bool valid = !grid[index]->solid;
    for (auto& e : children)
    {
        GridSprite* s = nullptr;
        s = dynamic_cast<GridSprite*>(e);
        if (s != nullptr)
        {
            valid = valid && !s->getGridPos().equals(Point(x, y));
        }
    }
    return valid;
}

int Grid::getSize()
{
    return size;
}
