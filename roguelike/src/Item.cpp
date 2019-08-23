#include "Item.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Stuff.hpp"

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

    if (!json_has(o, "name"))
    {
        std::cout << "missing name field\n";
        return;
    }
    name = o["name"];

    if (!json_has(o, "type"))
    {
        std::cout << "missing type field\n";
        return;
    }
    type = o["type"];

    if (!json_has(o, "data"))
    {
        std::cout << "missing data field\n";
        return;
    }
    for (auto& e : o["data"])
    {
        data.push_back(e.get<int>());
    }
}

const std::string Item::getName()
{
    return name;
}
