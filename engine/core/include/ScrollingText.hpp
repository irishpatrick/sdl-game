#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Timer.hpp"
#include <string>
#include <deque>
#include <vector>

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

		CORE_API void init(Context&, const std::string&, int);
		CORE_API void update();
		CORE_API void draw(Context&);
		CORE_API void next();
		CORE_API void addLine(const std::string&);

	private:
		SDL_Texture* tex;
		Font font;
		std::deque<std::string> lines;
		std::vector<SDL_Surface*> renderList;
		int lineIndex;
		int lineCount;
		bool running;
		int x;
		int y;
		SDL_Surface* surface;
		std::string renderLine;
		std::string currentLine;
		Timer timer;
	};
}