#pragma once

#include "context.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
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
        DebugInfo();
        ~DebugInfo();
        void init(Context&);
        void addLine(const std::string&);
        void draw(Context&);
        void flush();
    private:
        std::vector<std::string> lines;
        TTF_Font* font;
        SDL_Surface* glyphCache;
        GlyphMetrics* metrics;
    };

}