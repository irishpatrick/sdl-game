#pragma once

#include <engine.hpp>

using namespace engine;

class GridSprite;
class Tile;

class Grid : public Sprite
{
public:
    Grid();
    ~Grid();

    void addChild(Sprite* s);
    void load(Context&, const std::string&);
    void draw(Context&, float);
    int ctoi(int, int);
    Point itoc(int);
    bool checkMove(int, int);

    int getSize();

private:
    std::map<int, GridSprite*> childmap;
    Texture* atlas;
    std::vector<Tile*> tiles;
    std::vector<Tile*> grid;
    int size;
    int padding;
    int border;
    int w;
    int h;
};
