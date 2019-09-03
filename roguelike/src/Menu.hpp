#pragma once

#include <engine.hpp>
#include <vector>
#include <string>

using namespace engine;

class Menu : public Sprite
{
public:
    Menu();
    ~Menu();

    void init(Context&);
    void applyFormat(const std::string&);
    void pushOption(Context&, const std::string&);
    void draw(Context&, float);

    void moveCursor(int);

    int getChoice();

private:
    int choice;
    Color bgcolor;
    Color txtcolor;
    Canvas window;
    std::vector<Text*> opts;
    Canvas cursor;
};