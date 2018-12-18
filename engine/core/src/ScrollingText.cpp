#include "ScrollingText.hpp"

namespace engine
{
	void ScrollingText::init(Context& ctx, const std::string& fn, int size, int speed)
	{
		x = 0;
		y = 0;
		lineCount = 0;
		lineIndex = 0;
		font.init(ctx, fn, size);
		timer.setInterval(speed);
		timer.start();

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

		//surfaceTexture = SDL_CreateTexture(ctx.getRenderer(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, surface->w, surface->h);
		surfaceTexture = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
	}

	void ScrollingText::update()
	{
		if (running && timer.tick())
		{
			//std::cout << "tick" << std::endl;
			renderLine = currentLine.substr(0, lineIndex++);
			if (lineIndex > currentLine.size())
			{
				running = false;
			}
		}
	}

	void ScrollingText::draw(Context& ctx)
	{
		//std::cout << "running? " << running << std::endl;
		if (lineCount > 3)
		{
			SDL_FillRect(surface, nullptr, 0x00000000);
			lineCount = 1;
		}

		font.renderString(ctx, surface, renderLine, 0, (font.getLineSkip() * (lineCount - 1)));
		if (!running)
		{
			renderLine = "";
		}

		SDL_UpdateTexture(
			surfaceTexture,
			nullptr,
			surface->pixels,
			surface->pitch
		);
		
		SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = ctx.getWidth();
        r.h = ctx.getHeight();
		SDL_RenderCopy(ctx.getRenderer(), surfaceTexture, nullptr, &r);

		//std::cout << "renderLine: " << renderLine << std::endl;
		//std::cout << "rect: {" << r.x << "," << r.y << "," << r.w << "," << r.h << "}" << std::endl;
		//std::cout << std::endl;
	}

	void ScrollingText::addLine(const std::string& str)
	{
		lines.push_back(str);
	}

	void ScrollingText::next()
	{
		if (running)
		{
			return;
		}
		if (lines.size() == 0)
		{
			return;
		}
		timer.reset();
		lineIndex = 1;
		running = true;
		currentLine = lines.front();
		lines.pop_front();
		lineCount++;
	}

	void ScrollingText::addLines(const std::string& str, int width)
	{
		int start = 0;
		int end = 1;
		int current = 0;
		int lastSpaceIndex = -1;
		std::vector<int> spaces;
		while (start+1 < str.size())
		{
			std::string newLine = "";
			int calculatedW = 0;
			while (calculatedW < width)
			{
				std::string c = str.substr(current, 1);
				if (c == " ")
				{
					spaces.push_back(current);
				}
				newLine += c;
				calculatedW += font.getCharWidth(c);
				current++;
			}
			addLine(str.substr(start, current));
			start = current;
			calculatedW = 0;
		}
	}
}
