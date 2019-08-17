#pragma once

#include <engine.hpp>

using namespace engine;

class Tile;

class Grid : public Sprite
{
public:
    Grid();
    ~Grid();

    void load(Context&, const std::string&);
    void draw(Context&, float);

private:
    Texture* atlas;
    std::vector<Tile*> tiles;
    std::vector<Tile*> grid;
    int size;
    int padding;
    int w;
    int h;
};
