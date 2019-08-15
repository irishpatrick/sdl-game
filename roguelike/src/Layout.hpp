#pragma once

#include <engine.hpp>
#include <string>
#include <vector>

using namespace engine;

class Tilemap;

class Layout
{
public:
    Layout();
    ~Layout();

    void load(const std::string&);
    const std::string& get(int, int);
    void draw(Context&, float, Tilemap*);

    int width();
    int height();

private:
    char** map;
    std::vector<std::string> ref;
    int w;
    int h;
};
