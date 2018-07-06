#include "debuginfo.hpp"
#include <iostream>
#include <cstdio>

const std::string& chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

namespace engine {

    DebugInfo::DebugInfo() {

    }

    DebugInfo::~DebugInfo() {
        std::cout << "deallocating memory... ";
        if (metrics != nullptr) {
            free(metrics);
        }

        if (glyphCache != nullptr) {
            for (uint32_t i=0; i<chars.size(); i++) {
                if (glyphCache[i] != nullptr) {
                    SDL_FreeSurface(glyphCache[i]);
                }
            }
            free(glyphCache);
        }
        std::cout << "ok" << std::endl;
    }

    void DebugInfo::init(const std::string& fn, Context& ctx) {
        std::cout << "loading font... ";
        font = TTF_OpenFont(fn.c_str(), 12);
        if (font == nullptr) {
            std::cout << "error loading font: " << TTF_GetError() << std::endl;
        }
        std::cout << "ok" << std::endl;

        std::cout << "allocating memory...";
        metrics = (GlyphMetrics*)malloc(chars.size() * sizeof(GlyphMetrics));
        glyphCache = (SDL_Surface**)malloc(chars.size());
        std::cout << "ok" << std::endl;

        std::cout << "collecting glyph metrics... ";
        /*int i = 0;
        for (auto& c : chars) {
            GlyphMetrics* gm = &metrics[i];
            TTF_GlyphMetrics(font, c.c_str(), &gm->minx, &gm->maxx, &gm->miny, &gm->maxy, &gm->advance);
        }*/
        for (uint32_t i=0; i<chars.size(); i++) {
            char c = chars.at(i);
            GlyphMetrics* gm = &metrics[i];
            TTF_GlyphMetrics(font, c, &gm->minx, &gm->maxx, &gm->miny, &gm->maxy, &gm->advance);
        }
        std::cout << "ok" << std::endl;
    }

}
