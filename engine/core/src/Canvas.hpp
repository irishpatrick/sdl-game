#pragma once

#include <SDL.h>
#include <cstdint>
#include "Context.hpp"
#include <cairo.h>

namespace engine
{
    class Canvas
    {
    public:
        Canvas() : 
            texture(nullptr), 
            surface(nullptr),
            cairoSurface(nullptr),
            cr(nullptr),
            x(0), y(0), 
            w(0), h(0)
        {}
        ~Canvas();
        
        void create(Context&, uint32_t, uint32_t);
        void draw(Context&);
        cairo_t* getCairo();

        uint32_t getWidth();
        uint32_t getHeight();

    private:
        SDL_Texture* texture;
        SDL_Surface* surface;
        cairo_surface_t* cairoSurface;
        cairo_t* cr;
        float x;
        float y;
        uint32_t w;
        uint32_t h;
    };
}