#include "DebugInfo.hpp"
#include <iostream>
#include <cstdio>

//const std::string& chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

namespace engine
{

    DebugInfo::DebugInfo()
	{

    }

    DebugInfo::~DebugInfo()
	{

    }

    void DebugInfo::init(const std::string& fn, Context& ctx)
	{
        hasInit = true;
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

        out = SDL_CreateRGBSurface(
            0,
            ctx.getWidth(),
            ctx.getHeight(),
            32,
            rmask,
            gmask,
            bmask,
            amask
        );

		font.init(ctx, fn);
    }

	void DebugInfo::addLine(const std::string& str)
	{
		lines.push_back(str);
	}

	void DebugInfo::draw(Context& ctx)
	{
		int x = 0;
        int y = 0;

		for (auto& line : lines)
		{
			font.renderString(ctx, out, line, x, y);
			y += font.getLineSkip();
		}

        // draw final surface out
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = ctx.getWidth();
        r.h = ctx.getHeight();
        tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), out);
        SDL_RenderCopy(ctx.getRenderer(), tex, NULL, &r);
		SDL_DestroyTexture(tex);
	}

	void DebugInfo::flush()
	{
        lines.clear();
	}

    void DebugInfo::test()
	{
        /*for (uint32_t i=0; i<chars.size(); i++) {
            GlyphMetrics* gm = metrics[i];
            std::cout << chars.at(i) << " {" << gm->minx << ", " << gm->maxx << ", " << gm->miny << ", " << gm->maxy << ", " << gm->advance << "}" << std::endl;
        }*/
    }

}
