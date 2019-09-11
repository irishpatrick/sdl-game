#pragma once

#include <engine.hpp>
#include <vector>
#include <string>

using namespace engine;

class Textbox : public Sprite
{
public:
    Textbox();
    ~Textbox();

    void init();
    void fillDialogue(const std::string&);
    void play();
    void draw(float);
    void reset();

private:
    int currentLine;
    Canvas window;
    std::vector<Text*> lines;
};
