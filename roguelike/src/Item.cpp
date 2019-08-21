#include "Item.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

Item::Item()
{

}

Item::~Item()
{

}

void Item::load(const std::string& fn)
{
    std::ifstream in(fn);
    if (!in)
    {
        return;
    }
    json o;
    in >> o;
    in.close();

    
}
