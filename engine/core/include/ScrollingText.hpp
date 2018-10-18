#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Timer.hpp"
#include <string>
#include <deque>

namespace engine
{
	class ScrollingText
	{
	public:
		CORE_API ScrollingText()
		{
			tex = nullptr;
		}

		CORE_API ~ScrollingText()
		{

		}

		CORE_API void init(Context&, const std::string&);
		CORE_API void update();
		CORE_API void draw(Context&);
		CORE_API void next();
		CORE_API void addLine(const std::string&);

	private:
		Texture* tex;
		Font font;
		std::deque<std::string> lines;
		std::string currentLine;
		Timer timer;
	};
}