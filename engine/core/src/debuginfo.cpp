#include "debuginfo.hpp"
#include <iostream>
#include <cstdio>

const std::string& chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

namespace engine {

    DebugInfo::DebugInfo() {

    }

    DebugInfo::~DebugInfo() {

    }

    void DebugInfo::init(const std::string& fn, Context& ctx) {
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

        std::cout << "loading font... ";
        font = TTF_OpenFont(fn.c_str(), 200);
        if (font == nullptr) {
            std::cout << "error loading font: " << TTF_GetError() << std::endl;
        }
        std::cout << "ok" << std::endl;

        //std::cout << "allocating memory...";
        //metrics = (GlyphMetrics*)malloc(chars.size() * sizeof(GlyphMetrics));
        //glyphCache = (SDL_Surface**)malloc(chars.size());
        //std::cout << "ok" << std::endl;

        std::cout << "collecting glyph metrics... ";
        for (uint32_t i=0; i<chars.size(); i++) {
            char c = chars.at(i);
            GlyphMetrics* gm = (GlyphMetrics*)malloc(sizeof(GlyphMetrics));
            metrics.push_back(gm);
            TTF_GlyphMetrics(font, c, &gm->minx, &gm->maxx, &gm->miny, &gm->maxy, &gm->advance);
        }
        std::cout << "ok" << std::endl;

        // black
        SDL_Color color = {0,0,0};
        for (uint32_t i=0; i<chars.size(); i++) {
            char c = chars.at(i);
            glyphCache.push_back(TTF_RenderGlyph_Solid(font, c, color));
        }
    }

	void DebugInfo::addLine(const std::string& str) {
		lines.push_back(str);
	}

	void DebugInfo::draw(Context& ctx) {
        float x = 0;
        float y = 0;
        // loop through lines
        for (auto& line : lines) {
            // loop through characters in line
            for (auto& c : line) {
                size_t index = chars.find(c);
                GlyphMetrics* gm = metrics[static_cast<int>(index)];
                SDL_Surface* surf = glyphCache[static_cast<int>(index)];
                SDL_Rect rect;
                rect.x = x;
                rect.y = y;
                // set rect w
                rect.w = gm->maxx;
                // set rect h
                rect.h = gm->maxy;
                // blit to surface
                SDL_BlitSurface(surf, &rect, out, nullptr);

                // increment xs
                x += gm->advance;

            }
            x = 0;
            // add font height to y
            y += 10;
        }

        // draw final surface out
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = ctx.getWidth();
        r.h = ctx.getHeight();
        SDL_Texture* t = SDL_CreateTextureFromSurface(ctx.getRenderer(), out);
        SDL_RenderCopy(ctx.getRenderer(), t, NULL, &r);
        SDL_DestroyTexture(t);
	}

    void DebugInfo::drawLine(float x, float y, const std::string& str, Context& ctx) {
        for (uint32_t i=0; i<str.size(); i++) {
            char c = str.at(i);
            std::size_t loc = chars.find(str.at(i));
            GlyphMetrics* gm = metrics[static_cast<int>(loc)];

            SDL_Rect r;
            r.x = 10;
            r.y = 10;
            r.w = 100;
            r.h = 100;

			//SDL_BlitSurface();
        }
    }

	void DebugInfo::flush() {
        lines.clear();
	}

    void DebugInfo::test() {
        for (uint32_t i=0; i<chars.size(); i++) {
            GlyphMetrics* gm = metrics[i];
            std::cout << chars.at(i) << " {" << gm->minx << ", " << gm->maxx << ", " << gm->miny << ", " << gm->maxy << ", " << gm->advance << "}" << std::endl;
        }
    }

}
