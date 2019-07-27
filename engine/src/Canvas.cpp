#include "Canvas.hpp"
#include <iostream>

namespace engine
{
    Canvas::~Canvas()
    {
        /*if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
        }
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }*/
        if (tex != nullptr)
        {
            //tex->destroy();
        }
    }

    void Canvas::create(Context& ctx, uint32_t aw, uint32_t ah)
    {
        tex = new Texture();

        uint32_t rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
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
        w = aw;
        h = ah;
        if (w == 0 || h == 0)
        {
            std::cout << "warning: width and/or height could be zero" << std::endl;
        }
        SDL_Surface* surface = SDL_CreateRGBSurface
        (
            0, w, h, 32,
            rmask,
            gmask,
            bmask,
            amask
        );

        if (surface == NULL)
        {
            std::cout << "ERROR: failed to create SDL surface" << std::endl;
            return;
        }

        SDL_LockSurface(surface);

        //texture = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
        tex->create(ctx, surface);
        cairoSurface = cairo_image_surface_create_for_data
        (
            (uint8_t*)surface->pixels,
            CAIRO_FORMAT_ARGB32,
            surface->w,
            surface->h,
            surface->pitch
        );
        if (cairoSurface == NULL)
        {
            std::cout << "ERROR: failed to create cairo surface" << std::endl;
            return;
        }

        cr = cairo_create(cairoSurface);
        if (cr == NULL)
        {
            std::cout << "ERROR: failed to create cairo context" << std::endl;
            return;
        }
        ready = true;
    }

    cairo_t* Canvas::getCairo()
    {
        return cr;
    }

    cairo_surface_t* Canvas::getCairoSurface()
    {
        return cairoSurface;
    }

    void Canvas::draw(Context& ctx)
    {
        tex->update();

        SDL_Rect rect;
        rect.x = (int)x;
        rect.y = (int)y;
        rect.w = (int)w;
        rect.h = (int)h;
        SDL_RenderCopy(ctx.getRenderer(), tex->use(), NULL, &rect);
        
        cairo_save (cr);
        cairo_set_source_rgba (cr, 0 ,0 ,0 ,0);
        cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
        cairo_paint (cr);
        cairo_restore (cr);
    }

    uint32_t Canvas::getWidth()
    {
        return w;
    }

    uint32_t Canvas::getHeight()
    {
        return h;
    }

    bool Canvas::isReady()
    {
        return ready;
    }

    Texture* Canvas::toTexturePtr(Context& ctx)
    {
        /*Texture* t = new Texture();
        SDL_UnlockSurface(surface);
        t->create(ctx, surface);
        SDL_LockSurface(surface);
        return t;*/
        return nullptr;
    }

    Texture* Canvas::getTexture()
    {
        return tex;
    }
}