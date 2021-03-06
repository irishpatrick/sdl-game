#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <engine.hpp>

#include "Stats.hpp"
#include "Player.hpp"
#include "DialogueBox.hpp"

class Npc : public engine::KeyFrameSprite
{
public:
    Npc();
    ~Npc();

	void init(engine::Context&, const std::string&);
	void pushLine(const std::string&);
	void interact(engine::Sprite* s);
	void setDialogueBox(DialogueBox&);

private:
    std::vector<std::string> lines;
    Stats stats;
	DialogueBox* dialogue;
};
