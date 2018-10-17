#pragma once
#include "core_api.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
		CORE_API void init(Context&, const std::string&);
		CORE_API void renderString(Context&, SDL_Surface*, const std::string&, int, int);
		CORE_API SDL_Surface* getChar(char);
		CORE_API int getLineSkip();

	private:
		TTF_Font* font;
		std::vector<GlyphMetrics*> metrics;
		std::vector<SDL_Surface*> glyphCache;
	};
}