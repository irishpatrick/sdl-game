#include "Item.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Stuff.hpp"

using json = nlohmann::json;

std::map<std::string, Item*> Item::item_map;

Item::Item() :
    Sprite(),
    quantity(-1),
    name("none"),
    type("none"),
    flavor("none")
{

}

Item::~Item()
{
    
}

/*void Item::load(const std::string& fn)
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
    //tex = Assets::getTexture(o["texture"]);
    setTexture(Assets::getTexture(o["texture"]));

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
}*/

void Item::load(const std::string& fn)
{
    Item* item = new Item();

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
    item->name = o["name"];

    if (!json_has(o, "texture"))
    {
        std::cout << "missing texture field\n";
        return;
    }
    //tex = Assets::getTexture(o["texture"]);
    item->setTexture(Assets::getTexture(o["texture"]));

    if (!json_has(o, "animation"))
    {
        std::cout << "Missing animation field" << std::endl;
        return;
    }
    if (o["animation"] != "")
    {
        item->loadAnimation(o["animation"]);
        item->setCurrentAnimation("north");
    }

    if (!json_has(o, "type"))
    {
        std::cout << "missing type field\n";
        return;
    }
    item->type = o["type"];

    if (!json_has(o, "flavor"))
    {
        std::cout << "missing flavor text field" << std::endl;
        return;
    }
    item->flavor = o["flavor"];

    if (!json_has(o, "data"))
    {
        std::cout << "missing data field\n";
        return;
    }
    for (auto& e : o["data"])
    {
        item->data.push_back(e.get<int>());
    }

    item_map[item->name] = item;
}

Item Item::get(const std::string& name)
{
    if (item_map.find(name) == item_map.end())
    {
        std::cout << "item " << name << " does not exist" << std::endl;
        Item();
    }
    return *item_map[name];
}

const std::string Item::getName()
{
    return name;
}

const std::string Item::getType()
{
    return type;
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

bool Item::isConsumable()
{
    return type == "food";
}

bool Item::isEquippable()
{
    return type == "weapon" || type == "armor";
}

bool Item::isDroppable()
{
    return true;
}
