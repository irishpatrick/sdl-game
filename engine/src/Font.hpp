#pragma once

#include "core_api.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "Context.hpp"

namespace engine
{
	typedef struct _GlyphMetrics
	{
		int minx;
		int maxx;
		int miny;
		int maxy;
		int advance;
	} GlyphMetrics;

	class Font
	{
	public:
		Font();
		~Font();
		CORE_API void init(const std::string&, int);
		CORE_API void renderString(SDL_Surface*, const std::string&, int, int);
		CORE_API SDL_Surface* getChar(char);
		CORE_API int getLineSkip();
		CORE_API int getCharWidth(const std::string&);

	private:
		TTF_Font* font;
		std::vector<GlyphMetrics*> metrics;
		std::vector<SDL_Surface*> glyphCache;
	};
}
