#include "Npc.hpp"
#include <iostream>

Npc::Npc() : KeyFrameSprite()
{
	dialogue = nullptr;
}

Npc::~Npc() {

}

void Npc::setDialogueBox(DialogueBox& db)
{
	dialogue = &db;
}

void Npc::init(engine::Context& ctx, const std::string& fn)
{
	KeyFrameSprite::init(ctx, fn);
}

void Npc::pushLine(const std::string& str)
{
	lines.push_back(str);
}

void Npc::interact(engine::Sprite* sprite) {
    std::cout << "lines.size() " << lines.size() << std::endl;
    if (Player* player = dynamic_cast<Player*>(sprite)) {
        std::cout << "interacting with player" << std::endl;
		assert(dialogue != nullptr);
		dialogue->reset();
		for (auto& e : lines)
		{
			std::cout << e << std::endl;
			dialogue->addLine(e);
		}
		dialogue->next();
    }
}
