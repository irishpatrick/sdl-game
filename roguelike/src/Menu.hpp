#pragma once

#include <engine.hpp>
#include <vector>

using namespace engine;

class Menu : public Sprite
{
public:
    Menu();
    ~Menu();

    void init(Context&);
    void pushOption(Context&, const std::string&);
    void draw(Context&, float);

private:
    int choice;
    Color bgcolor;
    Color txtcolor;
    Canvas window;
    std::vector<Text*> opts;
    Canvas cursor;
};