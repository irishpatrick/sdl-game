#pragma once

#include <engine.hpp>
#include <iostream>

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
	void addLine(const std::string&);
	void next();
	bool hasNext();
	void reset();

    engine::ScrollingText text;
	engine::Sprite textBox;
};