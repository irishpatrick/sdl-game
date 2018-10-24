#pragma once

#include <engine.hpp>

class DialogueBox : public engine::Group
{
public:
    DialogueBox() : Group()
    {

    }

    ~DialogueBox()
    {

    }

	void init(engine::Context&, const std::string&);
	void update(float) override;
	void draw(engine::Context&) override;

    engine::ScrollingText text;
	engine::Sprite textBox;
};