#pragma once

#include <engine.hpp>
#include <vector>

using namespace engine;

class TextboxS
{
public:
    static void init();
    static void fillDialogue(const std::string&);
    static void play();
    static void draw();
    static void reset();
    static bool isVisible();
private:
    static int currentLine;
    static Canvas window;
    static std::vector<Text*> lines;
    static int x;
    static int y;
    static bool visible;
};