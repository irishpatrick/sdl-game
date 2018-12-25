#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Timer.hpp"
#include <string>
#include <deque>
#include <vector>
#include "Sprite.hpp"

namespace engine
{
	class ScrollingText : public Sprite
	{
	public:
		CORE_API ScrollingText()
		{
			surfaceTexture = nullptr;
		}

		CORE_API ~ScrollingText()
		{

		}

		CORE_API void init(Context&, const std::string&, int, int);
		CORE_API void update();
		CORE_API void draw(Context&);
		CORE_API void next();
		CORE_API void addLine(const std::string&);
		CORE_API void addLines(const std::string&, int);
		CORE_API bool hasNext();
		CORE_API void reset();

		int x;
		int y;

	private:
		SDL_Texture* surfaceTexture;
		Font font;
		std::deque<std::string> lines;
		std::vector<SDL_Surface*> renderList;
		int lineIndex;
		int lineCount;
		bool running;
		SDL_Surface* surface;
		std::string renderLine;
		std::string currentLine;
		Timer timer;
	};
}