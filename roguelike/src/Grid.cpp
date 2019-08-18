#include "Grid.hpp"
#include "Tile.hpp"
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
            (x * size) + (x * padding),
            (y * size) + (y * padding),
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

bool Grid::checkMove(int x, int y)
{
    int index = y * h + x;
    return !grid[index]->solid;
}

int Grid::getSize()
{
    return size;
}
