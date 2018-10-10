#include "Npc.hpp"
#include <iostream>

Npc::Npc() : KeyFrameSprite()
{

}

Npc::~Npc() {

}

void Npc::init(engine::Context& ctx, const std::string& fn)
{
	KeyFrameSprite::init(ctx, fn);
}

void Npc::pushLine(const std::string& str)
{
	lines.push_back(str);
}

void Npc::interact(engine::Sprite* sprite, ui::Dialogue* d) {
    std::cout << "lines.size() " << lines.size() << std::endl;
    if (Player* player = dynamic_cast<Player*>(sprite)) {
        std::cout << "interacting with player" << std::endl;
        //d->push(lines[0]);
    }
}
