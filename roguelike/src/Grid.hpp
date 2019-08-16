#pragma once

#include <engine.hpp>

using namespace engine;

struct GTile
{
    char tex;
    char solid;
};

class Grid : public Sprite
{
public:
    Grid();
    ~Grid();

    void load(Context&, const std::string&);

private:
    //Tile** map;
    Texture* atlas;
    std::vector<struct GTile*> tiles;
    std::vector<Texture*> tex;
    int w;
    int h;
};
