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
    Texture* getTexture();

    int getQuantity();
    void setQuantity(int);
    void incQuantity(int);


private:
    int quantity;
    std::string name;
    std::string type;
    std::string flavor;
    std::vector<int> data;
    Texture* tex;
};
