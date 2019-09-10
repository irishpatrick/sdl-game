#include "Item.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Stuff.hpp"

using json = nlohmann::json;

Item::Item() :
    quantity(0),
    name(""),
    type(""),
    flavor(""),
    tex(nullptr)
{

}

Item::~Item()
{

}

void Item::load(const std::string& fn)
{
    std::cout << "loading item " << fn << std::endl;
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

    if (!json_has(o, "texture"))
    {
        std::cout << "missing texture field\n";
        return;
    }
    tex = Assets::getTexture(o["texture"]);

    if (!json_has(o, "type"))
    {
        std::cout << "missing type field\n";
        return;
    }
    type = o["type"];

    if (!json_has(o, "flavor"))
    {
        std::cout << "missing flavor text field" << std::endl;
        return;
    }
    flavor = o["flavor"];

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

const std::string Item::getType()
{
    return type;
}

Texture* Item::getTexture()
{
    return tex;
}

int Item::getDataPoint(int index)
{
    return data[index];
}

int Item::getQuantity()
{
    return quantity;
}

void Item::setQuantity(int q)
{
    quantity = q;
}

void Item::incQuantity(int d)
{
    quantity += d;
}
