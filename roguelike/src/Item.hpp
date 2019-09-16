#pragma once

#include <string>
#include <vector>
#include <map>
#include <engine.hpp>

using namespace engine;

class Item : public Sprite
{
public:
    Item();
    ~Item();

    //void load(const std::string&);
    static void load(const std::string&);
    static Item get(const std::string&);

    const std::string getName();
    const std::string getType();

    int getDataPoint(int);

    int getQuantity();
    void setQuantity(int);
    void incQuantity(int);

    bool isEquippable();
    bool isConsumable();
    bool isDroppable();


private:
    int quantity;
    std::string name;
    std::string type;
    std::string flavor;
    std::vector<int> data;
    //Texture* tex;

    static std::map<std::string, Item*> item_map;
};
