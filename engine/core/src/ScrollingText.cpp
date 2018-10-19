#include "ScrollingText.hpp"

namespace engine
{
	void ScrollingText::init(Context& ctx, const std::string& fn)
	{
		font.init(ctx, fn);
		timer.setInterval(30);
	}

	void ScrollingText::update()
	{
		if (running && timer.tick())
		{
			renderLine = currentLine.substr(0, lineIndex++);
			if (lineIndex > currentLine.size())
			{
				running = false;
			}
		}
	}

	void ScrollingText::draw(Context& ctx)
	{
		font.renderString(ctx, surface, renderLine, x, y);
	}

	void ScrollingText::addLine(const std::string& str)
	{
		lines.push_front(str);
	}

	void ScrollingText::next()
	{
		running = true;
		lines.pop_back();
		currentLine = lines.back();
	}
}
