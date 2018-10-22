#include "ScrollingText.hpp"

namespace engine
{
	void ScrollingText::init(Context& ctx, const std::string& fn, int speed)
	{
		x = 0;
		y = 0;
		lineCount = 0;
		lineIndex = 0;
		font.init(ctx, fn);
		timer.setInterval(speed);

		uint32_t rmask, gmask, bmask, amask;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
        #endif

        surface = SDL_CreateRGBSurface(
            0,
            ctx.getWidth(),
            ctx.getHeight(),
            32,
            rmask,
            gmask,
            bmask,
            amask
        );
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
		if (lineCount > 3)
		{
			SDL_FillRect(surface, nullptr, 0x00000000);
			lineCount = 1;
		}

		font.renderString(ctx, surface, renderLine, x, y + (font.getLineSkip() * (lineCount - 1)));
		if (!running)
		{
			renderLine = "";
		}

		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
		SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = ctx.getWidth();
        r.h = ctx.getHeight();
		SDL_RenderCopy(ctx.getRenderer(), tex, nullptr, &r);
		SDL_DestroyTexture(tex);

	}

	void ScrollingText::addLine(const std::string& str)
	{
		lines.push_back(str);
	}

	void ScrollingText::next()
	{
		if (running)
		{
			std::cout << "cannot advance deque while running" << std::endl;
			return;
		}
		if (lines.size() == 0)
		{
			std::cout << "deque empty" << std::endl;
			return;
		}
		lineIndex = 1;
		running = true;
		currentLine = lines.front();
		lines.pop_front();
		lineCount++;
	}
}
