#include "npc.hpp"
#include <iostream>

Npc::Npc() {

}

Npc::~Npc() {

}

void Npc::interact(engine::Sprite* sprite, ui::Dialogue* d) {
    std::cout << "lines.size() " << lines.size() << std::endl;
    if (Player* player = dynamic_cast<Player*>(sprite)) {
        std::cout << "interacting with player" << std::endl;
        d->push(lines[0]);
    }
}

void Npc::loadJson(const std::string& fn) {
    std::ifstream in(fn);
    if (!in) {
        cout << "Npc: cannot load json " << fn << std::endl;
        return;
    }
    nlohmann::json o;
    in >> o;

    x = o["x"];
    y = o["y"];

    if (o.find("dialogue") != o.end()) {
        for (std::string line : o["dialogue"]) {
            lines.push_back(line);
        }
    }
}
