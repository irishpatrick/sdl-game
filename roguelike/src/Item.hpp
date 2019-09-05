#pragma once

#include <string>
#include <vector>
#include <engine.hpp>

using namespace engine;

class Item
{
public:
    Item();
    ~Item();

    void load(const std::string&);

    const std::string getName();

private:
    std::string name;
    std::string type;
    std::vector<int> data;
    Texture* tex;
};
