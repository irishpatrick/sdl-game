#pragma once

#include <engine.hpp>
#include <vector>

using namespace engine;

class Menu : public Sprite
{
public:
    Menu();
    ~Menu();

    void pushOption(Context&, const std::string&);
    void draw(Context&, float);

private:
    Canvas window;
    std::vector<Text> opts;
    Sprite cursor;
};