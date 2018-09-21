#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace engine {

	typedef struct {
        int minx;
        int maxx;
        int miny;
        int maxy;
        int advance;
    } GlyphMetrics;

    class DebugInfo {

    public:
        CORE_API DebugInfo();
        CORE_API ~DebugInfo();
        CORE_API void init(const std::string&, Context&);
        CORE_API void addLine(const std::string&);
        CORE_API void draw(Context&);
        CORE_API void drawLine(float, float, const std::string&, Context&);
        CORE_API void flush();
        CORE_API void test();


    private:
        std::vector<std::string> lines;
        TTF_Font* font;
        SDL_Surface* out;
        bool hasInit;

		std::vector<GlyphMetrics*> metrics;
		std::vector<SDL_Surface*> glyphCache;
    };

}
