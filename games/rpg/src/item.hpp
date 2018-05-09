#pragma once

#include <string>
#include <map>
#include <cstdint>
#include <engine.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

enum Mode {CONSUMABLE = 0, EQUIPPABLE = 1};

class Item {
public:
    Item();
    ~Item();

    // getters
    inline Mode getMode() {
        return mode;
    }

    json toJson();

    // setters

    // static
    static void loadItems(const string&);

private:
    Mode mode;
    uint32_t hp;
    uint32_t atk;
    uint32_t def;
    uint32_t spd;
    // static
    static json o;
};
