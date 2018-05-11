#include "npc.hpp"
#include <iostream>

Npc::Npc()
{
    //text_ = new engine::Text();
}
Npc::~Npc()
{
    //delete text_;
}

void Npc::interact(engine::Sprite* sprite) {
    if (Player* player = dynamic_cast<Player*>(sprite)) {
        std::cout << "interacting with player" << endl;
    }
}

void Npc::Json(const std::string& fn)
{
    std::ifstream in(fn);
    if (!in)
    {
        return;
    }
    nlohmann::json o;
    in >> o;

    x = o["x"];
    y = o["y"];

    if (engine::Util::JsonExists(o, "dialogue"))
    {
        for (string line : o["dialogue"])
        {
            dialogue_.push_back(line);
        }
    }
}
