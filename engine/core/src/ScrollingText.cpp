#include "ScrollingText.hpp"

namespace engine
{
	void ScrollingText::init(Context& ctx, const std::string& fn)
	{
		font.init(ctx, fn);
	}

	void ScrollingText::update()
	{

	}

	void ScrollingText::draw(Context& ctx)
	{

	}

	void ScrollingText::addLine(const std::string& str)
	{
		lines.push_front(str);
	}

	void ScrollingText::next()
	{
		lines.pop_back();
		currentLine = lines.back();
	}
}
