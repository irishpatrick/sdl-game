#pragma once

#include <SDL.h>
#include <cstdint>
#include "Context.hpp"
#include <cairo.h>

#include "Context.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"

namespace engine
{
    class Canvas : public Sprite
    {
    public:
        Canvas() :
            Sprite(),
            x(0), y(0),
            w(0), h(0),
            ready(false),
            tex(nullptr),
            cairoSurface(nullptr),
            surface(nullptr),
            cr(nullptr)
        {}
        virtual ~Canvas();
        
        void create(Context&, uint32_t, uint32_t);
        void create(Context&, Texture*, uint32_t, uint32_t);
        void attachTexture(Texture*);
        void clear();
        void draw(Context&);
        void draw(Context&, float, Point);
        cairo_t* getCairo();
        cairo_surface_t* getCairoSurface();
        bool isReady();
        uint32_t getWidth();
        uint32_t getHeight();

        void update();

        Texture* getTexture();

        void destroy();

        float x;
        float y;

    private:
        uint32_t w;
        uint32_t h;
        bool ready;
        Texture* tex;
        SDL_Surface* surface;
        cairo_surface_t* cairoSurface;
        cairo_t* cr;
    };
}