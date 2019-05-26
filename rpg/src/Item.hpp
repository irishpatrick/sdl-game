#pragma once

#include <string>
#include <engine.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum Type {TEMPORARY, PERMANENT, EQUIPPABLE};

class Item {
public:
    Item();
    ~Item();

    void load(const std::string&);
    void use(engine::Sprite*);

private:
    json o;
};
