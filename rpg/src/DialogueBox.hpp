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

	inline void addLine(const std::string& str)
	{
		text.addLine(str);
	}

	inline void next()
	{
		text.next();
	}

    engine::ScrollingText text;
	engine::Sprite textBox;
};