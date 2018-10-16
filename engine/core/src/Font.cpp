#include "Font.hpp"

const std::string& chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

namespace engine
{
	Font::Font()
	{

	}

	Font::~Font()
	{

	}

	void Font::init(const std::string& fn, Context& ctx)
	{
		font = TTF_OpenFont(fn.c_str(), 30);
		if (font == nullptr)
		{
			return;
		}
		
		SDL_Color color = { 255,255,255 };
		for (int i = 0; i < chars.size(); i++)
		{
			char c = chars.at(i);
			GlyphMetrics* gm = (GlyphMetrics*)malloc(sizeof(GlyphMetrics));
			metrics.push_back(gm);
			TTF_GlyphMetrics(font, c, &gm->minx, &gm->maxx, &gm->miny, &gm->maxy, &gm->advance);
			glyphCache.push_back(TTF_RenderGlyph_Blended(font, c, color));
		}
	}

	SDL_Surface getChar(char c)
	{

	}

	void Font::renderString(Context& ctx, SDL_Surface* out, const std::string& str, int x0, int y0)
	{
		int x = x0;
		int y = y0;
		for (auto& c : str)
		{
			//std::cout << "render " << c << std::endl;
			size_t index = chars.find(c);
			GlyphMetrics* gm = metrics[static_cast<int>(index)];
			SDL_Surface* surf = glyphCache[static_cast<int>(index)];
			SDL_Rect rect;
			SDL_Rect srcRect;
			rect.x = x;// +gm->minx;
			rect.y = y + TTF_FontDescent(font);
			//rect.y = y + gm->maxy;
			// set rect w
			//rect.w = (gm->maxx - gm->minx);
			// set rect h
			//rect.h = (gm->maxy - gm->miny);
			//std::cout << "rect: {" << rect.x << "," << rect.y << "}" << std::endl;

			// blit to surface
			SDL_BlitSurface(surf, nullptr, out, &rect);

			// increment xs
			x += gm->advance;

		}
	}
}
