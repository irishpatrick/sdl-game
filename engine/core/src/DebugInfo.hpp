#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Font.hpp"

namespace engine {

    class DebugInfo {

    public:
        CORE_API DebugInfo();
        CORE_API ~DebugInfo();
        CORE_API void init(const std::string&, Context&);
        CORE_API void addLine(const std::string&);
        CORE_API void draw(Context&);
        CORE_API void flush();
        CORE_API void test();


    private:
        std::vector<std::string> lines;
        //TTF_Font* font;
        SDL_Surface* out;
		SDL_Texture* tex;
        bool hasInit;
		Font font;

		std::vector<GlyphMetrics*> metrics;
		std::vector<SDL_Surface*> glyphCache;
    };

}
