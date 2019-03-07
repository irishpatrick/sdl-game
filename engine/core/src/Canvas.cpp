#include "Canvas.hpp"

namespace engine
{
    Canvas::~Canvas()
    {
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
        }
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
    }

    void Canvas::create(Context& ctx, uint32_t aw, uint32_t ah)
    {
        w = aw;
        h = ah;
        surface = SDL_CreateRGBSurface
        (
            0, w, h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff,
            0
        );

        //SDL_LockSurface(surface);

        texture = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
        cairoSurface = cairo_image_surface_create_for_data
        (
            (uint8_t*)surface->pixels,
            CAIRO_FORMAT_RGB24,
            surface->w,
            surface->h,
            surface->pitch
        );

        cr = cairo_create(cairoSurface);

        ready = true;
    }

    cairo_t* Canvas::getCairo()
    {
        return cr;
    }

    void Canvas::draw(Context& ctx)
    {
        //SDL_UnlockSurface(surface);
        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        //SDL_LockSurface(surface);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderCopy(ctx.getRenderer(), texture, NULL, &rect);
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
}