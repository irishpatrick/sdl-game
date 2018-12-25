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
	//void draw(engine::Context&) override;

	inline void addLine(const std::string& str)
	{
		text.addLine(str);
	}

	inline void next()
	{
		if (!text.hasNext())
		{
			std::cout << "text does not have next" << std::endl;
			setVisible(false);
			std::cout << "Group class visibility: " << isVisible() << std::endl;
		}
		else
		{
			std::cout << "text has next" << std::endl;
			setVisible(true);
			text.next();
		}
	}

	inline bool hasNext()
	{
		return text.hasNext();
	}

	inline void reset()
	{
		text.reset();
	}

    engine::ScrollingText text;
	engine::Sprite textBox;
};