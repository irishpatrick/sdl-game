#include "Grid.hpp"
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
    json o(in);
    in.close();

    if (!json_has(o, "atlas"))
    {
        return;
    }
    atlas = Assets::getTexture(o["atlas"]);

    if (!json_has(o, "tiles"))
    {
        return;
    }
    for (auto& e : o["tiles"])
    {
        struct GTile* t = (struct GTile*)malloc(sizeof(struct GTile));
        tex.push_back(new Texture(atlas->subTexture(ctx, (char)e[0].get<int>(), (char)e[1].get<int>(), (char)e[2].get<int>(), (char)e[3].get<int>())));
        t->tex = tex.size() - 1;
        t->solid = (char)e[4].get<int>();
        tiles.push_back(t);
    }

    if (!json_has(o, "data"))
    {
        return;
    }
    for (auto& e : o["data"])
    {

    }
}
